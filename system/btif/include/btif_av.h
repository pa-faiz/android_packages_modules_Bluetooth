/******************************************************************************
 *
 *  Copyright 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/**
 * BTIF AV API functions accessed internally.
 */

#ifndef BTIF_AV_H
#define BTIF_AV_H

#include <cstdint>
#include <vector>

#include "include/hardware/bt_av.h"
#include "types/raw_address.h"

#define APTX_HQ 0X1000
#define APTX_LL 0X2000
#define APTX_ULL_S 0X4000
#define APTX_ULL 0X5000//for 16 bit source
#define APTX_MODE_MASK 0X7000

#define APTX_HQ_LATENCY 2000
#define APTX_R2_1_HQ_LATENCY 3200
#define APTX_LL_LATENCY 700
#define APTX_ULL_LATENCY 700

#define QHS_SUPPORT_MASK 0x00000C00
#define QHS_SUPPORT_NOT_AVAILABLE 0x00000400
#define QHS_SUPPORT_AVAILABLE 0x00000800

/**
 * Enum to represent the type of local a2dp profile.
 */
enum class A2dpType { kSource, kSink, kUnknown };
/**
 * When the local device is A2DP source, get the address of the active peer.
 */
RawAddress btif_av_source_active_peer(void);

/**
 * When the local device is A2DP sink, get the address of the active peer.
 */
RawAddress btif_av_sink_active_peer(void);

/**
 * Check whether A2DP Sink is enabled.
 */
bool btif_av_is_sink_enabled(void);

/**
 * Check whether A2DP Source is enabled.
 */
bool btif_av_is_source_enabled(void);

/**
 * Start streaming.
 * @param local_a2dp_type type of local a2dp profile.
 */
void btif_av_stream_start(const A2dpType local_a2dp_type);

/**
 * Start streaming with latency setting.
 */
void btif_av_stream_start_with_latency(bool use_latency_mode);

/**
 * Stop streaming.
 *
 * @param peer_address the peer address or RawAddress::kEmpty to stop all peers
 */
void btif_av_stream_stop(const RawAddress& peer_address);

/**
 * Suspend streaming.
 */
void btif_av_stream_suspend(void);

/**
 * Start offload streaming.
 */
void btif_av_stream_start_offload(void);

/**
 * Check whether ready to start the A2DP stream.
 * @param local_a2dp_type type of local a2dp profile.
 */
bool btif_av_stream_ready(const A2dpType local_a2dp_type);

/**
 * Check whether A2DP flag is set OR not.
 * @param local_a2dp_type type of local a2dp profile and flag to check.
 */
bool btif_av_check_flag(const A2dpType local_a2dp_type, uint8_t flag);

/**
 * Check whether the A2DP stream is in started state and ready
 * for media start.
 * @param local_a2dp_type type of local a2dp profile.
 */
bool btif_av_stream_started_ready(const A2dpType local_a2dp_type);

/**
 * Check whether there is a connected peer (either Source or Sink)
 * @param local_a2dp_type type of local a2dp profile.
 */
bool btif_av_is_connected(const A2dpType local_a2dp_type);

/**
 * Get the Stream Endpoint Type of the Active peer.
 * @param local_a2dp_type type of local a2dp profile.
 *
 * @return the stream endpoint type: either AVDT_TSEP_SRC or AVDT_TSEP_SNK
 */
uint8_t btif_av_get_peer_sep(const A2dpType local_a2dp_type);

/**
 * Clear the remote suspended flag for the active peer.
 * @param local_a2dp_type type of local a2dp profile.
 */
void btif_av_clear_remote_suspend_flag(const A2dpType local_a2dp_type);

/**
 * Check whether the connected A2DP peer supports EDR.
 *
 * The value can be provided only if the remote peer is connected.
 * Otherwise, the answer will be always false.
 *
 * @param peer_address the peer address
 * @param local_a2dp_type type of local a2dp profile.
 * @return true if the remote peer is capable of EDR
 */
bool btif_av_is_peer_edr(const RawAddress& peer_address,
                         const A2dpType local_a2dp_type);

/**
 * Check whether the connected A2DP peer supports 3 Mbps EDR.
 *
 * The value can be provided only if the remote peer is connected.
 * Otherwise, the answer will be always false.
 *
 * @param peer_address the peer address
 * @param local_a2dp_type type of local a2dp profile.
 * @return true if the remote peer is capable of EDR and supports 3 Mbps
 */
bool btif_av_peer_supports_3mbps(const RawAddress& peer_address,
                                 const A2dpType local_a2dp_type);

/**
 * Check whether the mandatory codec is more preferred for this peer.
 *
 * @param peer_address the target peer address
 * @param local_a2dp_type type of local a2dp profile.
 * @return true if optional codecs are not preferred to be used
 */
bool btif_av_peer_prefers_mandatory_codec(const RawAddress& peer_address,
                                          const A2dpType local_a2dp_type);

/**
 * Report A2DP Source Codec State for a peer.
 *
 * @param peer_address the address of the peer to report
 * @param codec_config the codec config to report
 * @param codecs_local_capabilities the codecs local capabilities to report
 * @param codecs_selectable_capabilities the codecs selectable capabilities
 * to report
 */
void btif_av_report_source_codec_state(
    const RawAddress& peer_address,
    const btav_a2dp_codec_config_t& codec_config,
    const std::vector<btav_a2dp_codec_config_t>& codecs_local_capabilities,
    const std::vector<btav_a2dp_codec_config_t>&
        codecs_selectable_capabilities);

/**
 * Initialize / shut down the A2DP Source service.
 *
 * @param enable true to enable the A2DP Source service, false to disable it
 * @return BT_STATUS_SUCCESS on success, BT_STATUS_FAIL otherwise
 */
bt_status_t btif_av_source_execute_service(bool enable);

/**
 * Initialize / shut down the A2DP Sink service.
 *
 * @param enable true to enable the A2DP Sink service, false to disable it
 * @return BT_STATUS_SUCCESS on success, BT_STATUS_FAIL otherwise
 */
bt_status_t btif_av_sink_execute_service(bool enable);

/**
 * Peer ACL disconnected.
 *
 * @param peer_address the disconnected peer address
 * @param local_a2dp_type type of local a2dp profile.
 */
void btif_av_acl_disconnected(const RawAddress& peer_address,
                              const A2dpType local_a2dp_type);

/**
 * Dump debug-related information for the BTIF AV module.
 *
 * @param fd the file descriptor to use for writing the ASCII formatted
 * information
 */
void btif_debug_av_dump(int fd);

/**
 * Set the audio delay for the stream.
 *
 * @param peer_address the address of the peer to report
 * @param delay the delay to set in units of 1/10ms
 * @param local_a2dp_type type of local a2dp profile.
 */
void btif_av_set_audio_delay(const RawAddress& peer_address, uint16_t delay,
                             const A2dpType local_a2dp_type);

/**
 * Get the audio delay for the stream.
 * @param local_a2dp_type type of local a2dp profile.
 */
uint16_t btif_av_get_audio_delay(const A2dpType local_a2dp_type);

/**
 * Reset the audio delay and count of audio bytes sent to zero.
 */
void btif_av_reset_audio_delay(void);

/**
 * Called to disconnect peer device when
 *  remote initiatied offload start failed
 *
 * @param peer_address to disconnect
 *
 */
void btif_av_src_disconnect_sink(const RawAddress& peer_address);

/**
 *  check A2DP offload support enabled
 *  @param  none
 */
bool btif_av_is_a2dp_offload_enabled(void);

/**
 *  check A2DP offload enabled and running
 *  @param  none
 */
bool btif_av_is_a2dp_offload_running(void);

/**
 * Check whether peer device is silenced
 *
 * @param peer_address to check
 *
 */
bool btif_av_is_peer_silenced(const RawAddress& peer_address);

/**
 * check the a2dp connect status
 *
 * @param peer_address : checked device address
 * @param local_a2dp_type type of local a2dp profile.
 *
 */
bool btif_av_is_connected_addr(const RawAddress& peer_address,
                               const A2dpType local_a2dp_type);

/**
 * Set the dynamic audio buffer size
 *
 * @param dynamic_audio_buffer_size to set
 */
void btif_av_set_dynamic_audio_buffer_size(uint8_t dynamic_audio_buffer_size);

/**
 * Enable/disable the low latency
 *
 * @param is_low_latency to set
 */
void btif_av_set_low_latency(bool is_low_latency);

/**
 * Update Codec Mode
 *
 * @param
 */
void btif_av_update_codec_mode();

/**
 * Update Source Metadata
 *
 * @param source_metadata to set
 */
void btif_av_update_source_metadata(bool is_Gaming_Enabled);

/**
 * Set Low Latency for Spatial Audio
 *
 * @param low_latency to set
 */
void btif_av_set_low_latency_spatial_audio(bool is_low_latency);

/*
 * Dual Mode Enabled check
 */
bool btif_av_is_dual_mode_enabled();

/*
 * Update Metadata Context
 */
void btif_av_metadata_update(uint16_t context);

/*
 * Returns the AptX Mode
 */
uint16_t btif_av_get_aptx_mode_info();

/*
 * Updates the AptX Mode
 */
void btif_av_update_aptx_mode_info();

/**
 * Initiate an AV connection after 3s timeout to peer audio sink
 * @param handle bta handle
 * @param peer_addr peer address
 */
void btif_av_connect_sink_delayed(uint8_t handle,
                                  const RawAddress& peer_address);

/**
 * Check whether A2DP Source is enabled.
 */
extern bool btif_av_is_source_enabled(void);
extern bool btif_av_both_enable(void);
extern bool btif_av_src_sink_coexist_enabled(void);
extern bool btif_av_is_sink_enabled(void);
extern bool btif_av_is_connected_addr(const RawAddress& peer_address,
                                      const A2dpType local_a2dp_type);
extern bool btif_av_peer_is_connected_sink(const RawAddress& peer_address);
extern bool btif_av_peer_is_connected_source(const RawAddress& peer_address);
extern bool btif_av_peer_is_sink(const RawAddress& peer_address);
extern bool btif_av_peer_is_source(const RawAddress& peer_address);

#endif /* BTIF_AV_H */
