#include "hands.h"
#include "../utils/vec.h"
#include "../view/context.h"
#include "../view/draw.h"
#include "event.h"
#include "hand.h"
#include "player.h"
#include "wind.h"
#include <stdlib.h>

typedef struct Hands {
    Hand *hands[4];
    Player player;
} Hands;

void hands_draw(Hands *hands, Settings settings) {
    for (int i = 0; i < 4; i++) {
        hand_draw(hands->hands[i], settings);
    }
}

Hands *hands_empty() {
    Hands *res = calloc(sizeof(*res), 1);
    for (Player player = Player0; player <= Player3; player++) {
        res->hands[player] = hand_empty(player);
    }
    res->player = Player0;
    return res;
}

void hands_pick_from(Hands *hands, vec(Tile *) * from, Settings settings) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            hand_pick_from(hands->hands[i], from, settings);
        }
        hand_sort(hands->hands[i]);
    }
}

Hand *hands_get(Hands *hands, Player player) { return hands->hands[player]; }

void hands_free(Hands *hands) {
    for (int i = 0; i < 4; i++) {
        hand_free(hands->hands[i]);
    }
    free(hands);
}

void hands_update(Hands *hands, vec(Tile *) * tiles, Context ctx,
                  Settings settings) {
    reset_hover_pressed();
    Hand *hand = hands->hands[hands->player];
    for (Player player = Player0; player <= Player3; player++) {
        hand_update_pos_transi(hands->hands[player]);
    }
    if (hand_update(hand, tiles, ctx, settings)) {
        player_next(&hands->player);
    }
    int hand_hover = hand_get_hand_hover(hand);
    if (hand_hover != -1) {
        tile_hover_set(hand_closed_tiles(hand)[hand_hover]);
    }
}

void hands_handle_event(Hands *hands, Event event) {
    switch (event.type) {
    case DISCARD: {
        Wind wind = event.discard.wind;
        Tile *tile = event.discard.tile;
        printf("TODO Discard\n");
        break;
    }
    default:
        printf("TODO Other Event\n");
    }
}
