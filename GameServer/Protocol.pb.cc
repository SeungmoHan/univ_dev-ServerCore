// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protocol.proto

#include "Protocol.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace Protocol {
constexpr BuffData::BuffData(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : victims_()
  , _victims_cached_byte_size_()
  , buffid_(uint64_t{0u})
  , remaintime_(0){}
struct BuffDataDefaultTypeInternal {
  constexpr BuffDataDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~BuffDataDefaultTypeInternal() {}
  union {
    BuffData _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT BuffDataDefaultTypeInternal _BuffData_default_instance_;
constexpr SC_TEST::SC_TEST(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : buff_()
  , id_(uint64_t{0u})
  , hp_(0u)
  , attack_(0u){}
struct SC_TESTDefaultTypeInternal {
  constexpr SC_TESTDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~SC_TESTDefaultTypeInternal() {}
  union {
    SC_TEST _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT SC_TESTDefaultTypeInternal _SC_TEST_default_instance_;
constexpr CS_TEST::CS_TEST(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : buff_()
  , id_(uint64_t{0u})
  , hp_(0u)
  , attack_(0u){}
struct CS_TESTDefaultTypeInternal {
  constexpr CS_TESTDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~CS_TESTDefaultTypeInternal() {}
  union {
    CS_TEST _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT CS_TESTDefaultTypeInternal _CS_TEST_default_instance_;
}  // namespace Protocol
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Protocol_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_Protocol_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Protocol_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Protocol_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::BuffData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::BuffData, buffid_),
  PROTOBUF_FIELD_OFFSET(::Protocol::BuffData, remaintime_),
  PROTOBUF_FIELD_OFFSET(::Protocol::BuffData, victims_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::SC_TEST, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::SC_TEST, id_),
  PROTOBUF_FIELD_OFFSET(::Protocol::SC_TEST, hp_),
  PROTOBUF_FIELD_OFFSET(::Protocol::SC_TEST, attack_),
  PROTOBUF_FIELD_OFFSET(::Protocol::SC_TEST, buff_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::CS_TEST, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::CS_TEST, id_),
  PROTOBUF_FIELD_OFFSET(::Protocol::CS_TEST, hp_),
  PROTOBUF_FIELD_OFFSET(::Protocol::CS_TEST, attack_),
  PROTOBUF_FIELD_OFFSET(::Protocol::CS_TEST, buff_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Protocol::BuffData)},
  { 8, -1, sizeof(::Protocol::SC_TEST)},
  { 17, -1, sizeof(::Protocol::CS_TEST)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_BuffData_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_SC_TEST_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_CS_TEST_default_instance_),
};

const char descriptor_table_protodef_Protocol_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016Protocol.proto\022\010Protocol\"\?\n\010BuffData\022\016"
  "\n\006buffId\030\001 \001(\004\022\022\n\nremainTime\030\002 \001(\002\022\017\n\007vi"
  "ctims\030\003 \003(\004\"S\n\007SC_TEST\022\n\n\002id\030\001 \001(\004\022\n\n\002hp"
  "\030\002 \001(\r\022\016\n\006attack\030\003 \001(\r\022 \n\004buff\030\004 \003(\0132\022.P"
  "rotocol.BuffData\"S\n\007CS_TEST\022\n\n\002id\030\001 \001(\004\022"
  "\n\n\002hp\030\002 \001(\r\022\016\n\006attack\030\003 \001(\r\022 \n\004buff\030\004 \003("
  "\0132\022.Protocol.BuffDatab\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Protocol_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Protocol_2eproto = {
  false, false, 269, descriptor_table_protodef_Protocol_2eproto, "Protocol.proto", 
  &descriptor_table_Protocol_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_Protocol_2eproto::offsets,
  file_level_metadata_Protocol_2eproto, file_level_enum_descriptors_Protocol_2eproto, file_level_service_descriptors_Protocol_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_Protocol_2eproto_getter() {
  return &descriptor_table_Protocol_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_Protocol_2eproto(&descriptor_table_Protocol_2eproto);
namespace Protocol {

// ===================================================================

class BuffData::_Internal {
 public:
};

BuffData::BuffData(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  victims_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.BuffData)
}
BuffData::BuffData(const BuffData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      victims_(from.victims_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&buffid_, &from.buffid_,
    static_cast<size_t>(reinterpret_cast<char*>(&remaintime_) -
    reinterpret_cast<char*>(&buffid_)) + sizeof(remaintime_));
  // @@protoc_insertion_point(copy_constructor:Protocol.BuffData)
}

void BuffData::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&buffid_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&remaintime_) -
    reinterpret_cast<char*>(&buffid_)) + sizeof(remaintime_));
}

BuffData::~BuffData() {
  // @@protoc_insertion_point(destructor:Protocol.BuffData)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void BuffData::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void BuffData::ArenaDtor(void* object) {
  BuffData* _this = reinterpret_cast< BuffData* >(object);
  (void)_this;
}
void BuffData::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void BuffData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void BuffData::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.BuffData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  victims_.Clear();
  ::memset(&buffid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&remaintime_) -
      reinterpret_cast<char*>(&buffid_)) + sizeof(remaintime_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* BuffData::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 buffId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          buffid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // float remainTime = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 21)) {
          remaintime_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // repeated uint64 victims = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt64Parser(_internal_mutable_victims(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24) {
          _internal_add_victims(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* BuffData::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.BuffData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 buffId = 1;
  if (this->buffid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_buffid(), target);
  }

  // float remainTime = 2;
  if (!(this->remaintime() <= 0 && this->remaintime() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(2, this->_internal_remaintime(), target);
  }

  // repeated uint64 victims = 3;
  {
    int byte_size = _victims_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteUInt64Packed(
          3, _internal_victims(), byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.BuffData)
  return target;
}

size_t BuffData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.BuffData)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated uint64 victims = 3;
  {
    size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      UInt64Size(this->victims_);
    if (data_size > 0) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
            static_cast<::PROTOBUF_NAMESPACE_ID::int32>(data_size));
    }
    int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(data_size);
    _victims_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // uint64 buffId = 1;
  if (this->buffid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_buffid());
  }

  // float remainTime = 2;
  if (!(this->remaintime() <= 0 && this->remaintime() >= 0)) {
    total_size += 1 + 4;
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void BuffData::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.BuffData)
  GOOGLE_DCHECK_NE(&from, this);
  const BuffData* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BuffData>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.BuffData)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.BuffData)
    MergeFrom(*source);
  }
}

void BuffData::MergeFrom(const BuffData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.BuffData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  victims_.MergeFrom(from.victims_);
  if (from.buffid() != 0) {
    _internal_set_buffid(from._internal_buffid());
  }
  if (!(from.remaintime() <= 0 && from.remaintime() >= 0)) {
    _internal_set_remaintime(from._internal_remaintime());
  }
}

void BuffData::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.BuffData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BuffData::CopyFrom(const BuffData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.BuffData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BuffData::IsInitialized() const {
  return true;
}

void BuffData::InternalSwap(BuffData* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  victims_.InternalSwap(&other->victims_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(BuffData, remaintime_)
      + sizeof(BuffData::remaintime_)
      - PROTOBUF_FIELD_OFFSET(BuffData, buffid_)>(
          reinterpret_cast<char*>(&buffid_),
          reinterpret_cast<char*>(&other->buffid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata BuffData::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Protocol_2eproto_getter, &descriptor_table_Protocol_2eproto_once,
      file_level_metadata_Protocol_2eproto[0]);
}

// ===================================================================

class SC_TEST::_Internal {
 public:
};

SC_TEST::SC_TEST(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  buff_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.SC_TEST)
}
SC_TEST::SC_TEST(const SC_TEST& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      buff_(from.buff_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&attack_) -
    reinterpret_cast<char*>(&id_)) + sizeof(attack_));
  // @@protoc_insertion_point(copy_constructor:Protocol.SC_TEST)
}

void SC_TEST::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&id_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&attack_) -
    reinterpret_cast<char*>(&id_)) + sizeof(attack_));
}

SC_TEST::~SC_TEST() {
  // @@protoc_insertion_point(destructor:Protocol.SC_TEST)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void SC_TEST::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void SC_TEST::ArenaDtor(void* object) {
  SC_TEST* _this = reinterpret_cast< SC_TEST* >(object);
  (void)_this;
}
void SC_TEST::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void SC_TEST::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void SC_TEST::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.SC_TEST)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  buff_.Clear();
  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&attack_) -
      reinterpret_cast<char*>(&id_)) + sizeof(attack_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SC_TEST::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 hp = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          hp_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 attack = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          attack_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated .Protocol.BuffData buff = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_buff(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<34>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* SC_TEST::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.SC_TEST)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 id = 1;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_id(), target);
  }

  // uint32 hp = 2;
  if (this->hp() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_hp(), target);
  }

  // uint32 attack = 3;
  if (this->attack() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_attack(), target);
  }

  // repeated .Protocol.BuffData buff = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_buff_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(4, this->_internal_buff(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.SC_TEST)
  return target;
}

size_t SC_TEST::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.SC_TEST)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Protocol.BuffData buff = 4;
  total_size += 1UL * this->_internal_buff_size();
  for (const auto& msg : this->buff_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // uint64 id = 1;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_id());
  }

  // uint32 hp = 2;
  if (this->hp() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_hp());
  }

  // uint32 attack = 3;
  if (this->attack() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_attack());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SC_TEST::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.SC_TEST)
  GOOGLE_DCHECK_NE(&from, this);
  const SC_TEST* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<SC_TEST>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.SC_TEST)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.SC_TEST)
    MergeFrom(*source);
  }
}

void SC_TEST::MergeFrom(const SC_TEST& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.SC_TEST)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  buff_.MergeFrom(from.buff_);
  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.hp() != 0) {
    _internal_set_hp(from._internal_hp());
  }
  if (from.attack() != 0) {
    _internal_set_attack(from._internal_attack());
  }
}

void SC_TEST::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.SC_TEST)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SC_TEST::CopyFrom(const SC_TEST& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.SC_TEST)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SC_TEST::IsInitialized() const {
  return true;
}

void SC_TEST::InternalSwap(SC_TEST* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  buff_.InternalSwap(&other->buff_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(SC_TEST, attack_)
      + sizeof(SC_TEST::attack_)
      - PROTOBUF_FIELD_OFFSET(SC_TEST, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata SC_TEST::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Protocol_2eproto_getter, &descriptor_table_Protocol_2eproto_once,
      file_level_metadata_Protocol_2eproto[1]);
}

// ===================================================================

class CS_TEST::_Internal {
 public:
};

CS_TEST::CS_TEST(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  buff_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.CS_TEST)
}
CS_TEST::CS_TEST(const CS_TEST& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      buff_(from.buff_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&attack_) -
    reinterpret_cast<char*>(&id_)) + sizeof(attack_));
  // @@protoc_insertion_point(copy_constructor:Protocol.CS_TEST)
}

void CS_TEST::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&id_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&attack_) -
    reinterpret_cast<char*>(&id_)) + sizeof(attack_));
}

CS_TEST::~CS_TEST() {
  // @@protoc_insertion_point(destructor:Protocol.CS_TEST)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void CS_TEST::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void CS_TEST::ArenaDtor(void* object) {
  CS_TEST* _this = reinterpret_cast< CS_TEST* >(object);
  (void)_this;
}
void CS_TEST::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void CS_TEST::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void CS_TEST::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.CS_TEST)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  buff_.Clear();
  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&attack_) -
      reinterpret_cast<char*>(&id_)) + sizeof(attack_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CS_TEST::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 hp = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          hp_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 attack = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          attack_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated .Protocol.BuffData buff = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_buff(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<34>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* CS_TEST::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.CS_TEST)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 id = 1;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_id(), target);
  }

  // uint32 hp = 2;
  if (this->hp() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_hp(), target);
  }

  // uint32 attack = 3;
  if (this->attack() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_attack(), target);
  }

  // repeated .Protocol.BuffData buff = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_buff_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(4, this->_internal_buff(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.CS_TEST)
  return target;
}

size_t CS_TEST::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.CS_TEST)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Protocol.BuffData buff = 4;
  total_size += 1UL * this->_internal_buff_size();
  for (const auto& msg : this->buff_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // uint64 id = 1;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_id());
  }

  // uint32 hp = 2;
  if (this->hp() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_hp());
  }

  // uint32 attack = 3;
  if (this->attack() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_attack());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void CS_TEST::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.CS_TEST)
  GOOGLE_DCHECK_NE(&from, this);
  const CS_TEST* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<CS_TEST>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.CS_TEST)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.CS_TEST)
    MergeFrom(*source);
  }
}

void CS_TEST::MergeFrom(const CS_TEST& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.CS_TEST)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  buff_.MergeFrom(from.buff_);
  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.hp() != 0) {
    _internal_set_hp(from._internal_hp());
  }
  if (from.attack() != 0) {
    _internal_set_attack(from._internal_attack());
  }
}

void CS_TEST::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.CS_TEST)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CS_TEST::CopyFrom(const CS_TEST& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.CS_TEST)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CS_TEST::IsInitialized() const {
  return true;
}

void CS_TEST::InternalSwap(CS_TEST* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  buff_.InternalSwap(&other->buff_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(CS_TEST, attack_)
      + sizeof(CS_TEST::attack_)
      - PROTOBUF_FIELD_OFFSET(CS_TEST, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata CS_TEST::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Protocol_2eproto_getter, &descriptor_table_Protocol_2eproto_once,
      file_level_metadata_Protocol_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::BuffData* Arena::CreateMaybeMessage< ::Protocol::BuffData >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::BuffData >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::SC_TEST* Arena::CreateMaybeMessage< ::Protocol::SC_TEST >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::SC_TEST >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::CS_TEST* Arena::CreateMaybeMessage< ::Protocol::CS_TEST >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::CS_TEST >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
