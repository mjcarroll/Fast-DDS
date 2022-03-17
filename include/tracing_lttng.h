// Copyright 2022 Christophe Bedard
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Provide fake header guard for cpplint
#undef _TRACING_LTTNG_H_
#ifndef _TRACING_LTTNG_H_
#define _TRACING_LTTNG_H_

#include "fastrtps/config.h"

#ifndef DDS_HAS_LTTNG_TRACING

#define TRACEPOINT(event_name, ...) ((void) (0))

#else  // DDS_HAS_LTTNG_TRACING

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER dds

#define TRACEPOINT(event_name, ...) \
  tracepoint(TRACEPOINT_PROVIDER, event_name, __VA_ARGS__)

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "tracing_lttng.h"

#if !defined(__TRACING_LTTNG_H_) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define __TRACING_LTTNG_H_

#include <lttng/tracepoint.h>

#include <stdint.h>
#include <stdbool.h>

// GUIDs are split into a prefix of 12 bytes and an entity ID of 4 bytes, for a total of 16 bytes
#define DDS_GUID_GUIDPREFIX_STORAGE_SIZE 12u
#define DDS_GUID_ENTITYID_STORAGE_SIZE 4u

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  create_writer,
  TP_ARGS(
    const void *, writer_arg,
    const char *, topic_name_arg,
    const uint8_t *, gid_prefix_arg,
    const uint8_t *, gid_entity_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, writer, writer_arg)
    ctf_string(topic_name, topic_name_arg)
    ctf_array(uint8_t, gid_prefix, gid_prefix_arg, DDS_GUID_GUIDPREFIX_STORAGE_SIZE)
    ctf_array(uint8_t, gid_entity, gid_entity_arg, DDS_GUID_ENTITYID_STORAGE_SIZE)
  )
)

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  create_reader,
  TP_ARGS(
    const void *, reader_arg,
    const char *, topic_name_arg,
    const uint8_t *, gid_prefix_arg,
    const uint8_t *, gid_entity_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, reader, reader_arg)
    ctf_string(topic_name, topic_name_arg)
    ctf_array(uint8_t, gid_prefix, gid_prefix_arg, DDS_GUID_GUIDPREFIX_STORAGE_SIZE)
    ctf_array(uint8_t, gid_entity, gid_entity_arg, DDS_GUID_ENTITYID_STORAGE_SIZE)
  )
)

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  write_pre,
  TP_ARGS(
    const void *, writer_arg,
    const void *, data_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, writer, writer_arg)
    ctf_integer_hex(const void *, data, data_arg)
  )
)

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  write,
  TP_ARGS(
    const void *, writer_arg,
    int64_t, timestamp_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, writer, writer_arg)
    ctf_integer(int64_t, timestamp, timestamp_arg)
  )
)

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  read,
  TP_ARGS(
    const void *, reader_arg,
    const void *, buffer_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, reader, reader_arg)
    ctf_integer_hex(const void *, buffer, buffer_arg)
  )
)

#endif  // __TRACING_LTTNG_H_

#include <lttng/tracepoint-event.h>

#endif  // DDS_HAS_LTTNG_TRACING

#endif  // _TRACING_LTTNG_H_
