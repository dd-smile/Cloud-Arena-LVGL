#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
*打开文件或url并设置窗口大小
 */
int mm_player_open(const char *fp, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * Close file or url
 */
int mm_player_close(void);      //关闭文件或url

/**
 * Stop playing
 */
int mm_player_pause(void);      //暂停播放

/**
 * Resume playing
 */
int mm_player_resume(void);     //恢复播放

/**
 * Seek file forward or backward in the current position for time
 */
int mm_player_seek(double time);        //在当前位置向前或向后搜索文件

/**
 * Seek file to the setting time
 */
int mm_player_seek2time(double time);       //将文件定位到设置的时间

/**
 * Get the current playing time of video file
 */
int mm_player_getposition(double *position);        //获取视频文件的当前播放时间

/**
 * Get the total time of video file
 */
int mm_player_getduration(double *duration);        //获取视频文件的总时间

/**
 * Set the audio volumn.
 * volumn = [0]~[100]
 */
int mm_player_set_volumn(int volumn);           //设置音量

/**
 * Mute the audio.
 * volumn = false/true
 */
int mm_player_set_mute(bool mute);      //设置静音

/**
 * Set the windows size.
 * The function is valid when we call mm_player_set_opts("enable_scaler", "", 1) before mm_player_open.
 */
int mm_player_set_window(int x, int y, int width, int height);      //设置窗口大小

/**
 * Set player others options.
 * key: option name; value: reserved; flags: option value. Such as:
 * mm_player_set_opts("video_only", "", 0); -- "1"=enable; "0"=disable
 * mm_player_set_opts("audio_only", "", 0); -- "1"=enable; "0"=disable
 * mm_player_set_opts("video_rotate", "", AV_ROTATE_NONE);
 * mm_player_set_opts("video_ratio", "", AV_SCREEN_MODE);
 * mm_player_set_opts("audio_device", "", 0); -- "0"=panel; "2/3"=hdmi
 * mm_player_set_opts("audio_layout", "", AV_CH_LAYOUT_MONO); -- set audio layout
 * mm_player_set_opts("enable_scaler", "", 1); -- enable scaler module, such as: divp/vpe, "1"=enable; "0"=disable
 * mm_player_set_opts("resolution", "921600", 0); -- set the max resolution of video, 921600 = 1280 x 720
 * mm_player_set_opts("play_mode", "", AV_LOOP); -- set player mode, such as loop or once.
 */
int mm_player_set_opts(const char *key, const char *value, int flags);    //设置播放器其他选项

/**
 * Get player real status.
 * Return value:
 * AV_ACODEC_ERROR  -- video deocder error
 * AV_VCODEC_ERROR  -- audio deocder error
 * AV_NOSYNC        -- audio and video is not sync
 * AV_READ_TIMEOUT  -- read data from network over time out
 * AV_NO_NETWORK    -- not find network
 * AV_INVALID_FILE  -- the file name or url is invalid
 * AV_NOTHING       -- player is normal
 * AV_PLAY_COMPLETE -- end of file
 * AV_PLAY_PAUSE    -- stoping player
 */
int mm_player_get_status(void);     //获取播放器实时状态

/**
 * Enable/disable display if player is working. Clear screen if player is closed.
 * Please call the api after exit player to clear display.
 */
int mm_player_flush_screen(bool enable);            //启用/禁用显示器，如果播放器正在工作，请在退出播放器后调用该API以清除显示器

#ifdef __cplusplus
}
#endif // __cplusplu

#endif
