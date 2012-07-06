/* -*- c++ -*- */

#ifndef _NHK_ROLLER_AUTO_H_
#define _NHK_ROLLER_AUTO_H_

#ifndef __cplusplus
#include <stdbool.h>
#endif
#include "indicator.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern IndicatorID difference_indicator_id;

    double auto_get_target_position(void);
    bool auto_set_target_position_by_key(char key);
    void auto_set_target_position_by_value(double target);
    void auto_print_target_position_list(void);

#ifdef __cplusplus
}
#endif

#endif /* _NHK_ROLLER_AUTO_H_ */

