#ifndef RTW_HEADER_Copy_of_test_v_control_and_i_control_with_droop_copy_cap_host_h_
#define RTW_HEADER_Copy_of_test_v_control_and_i_control_with_droop_copy_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} Copy_of_test_v_control_and_i_control_with_droop_copy_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C" {

#endif

  void
    Copy_of_test_v_control_and_i_control_with_droop_copy_host_InitializeDataMapInfo
    (Copy_of_test_v_control_and_i_control_with_droop_copy_host_DataMapInfo_T
     *dataMap, const char *path);

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                 /* RTW_HEADER_Copy_of_test_v_control_and_i_control_with_droop_copy_cap_host_h_ */

/* EOF: Copy_of_test_v_control_and_i_control_with_droop_copy_capi_host.h */
