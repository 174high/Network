LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= sys_cmd.c
LOCAL_MODULE:= sys_cmd

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= sys_cmd_ser.c
LOCAL_MODULE:= sys_cmd_ser

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= sys_cmd_clt.c
LOCAL_MODULE:= sys_cmd_clt

include $(BUILD_EXECUTABLE)
