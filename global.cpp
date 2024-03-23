#include "global.h"

#include <utility>

int cnt_good = 0;
int final_score = 0;

int cnt_barriar = 0, cnt_ground = 0;

int choose[kMAX_ROBOT];

inline bool is_map_open() { return cnt_barriar == 0 && cnt_ground == 35501; }
inline bool is_map_close() {
    return cnt_barriar == 10152 && cnt_ground == 12466;
}
inline bool is_map_unknown() { return !is_map_open() && !is_map_close(); }