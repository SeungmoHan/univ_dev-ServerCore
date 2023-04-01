// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protocol.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Protocol_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Protocol_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Protocol_2eproto;
namespace Protocol {
class BuffData;
struct BuffDataDefaultTypeInternal;
extern BuffDataDefaultTypeInternal _BuffData_default_instance_;
class CS_TEST;
struct CS_TESTDefaultTypeInternal;
extern CS_TESTDefaultTypeInternal _CS_TEST_default_instance_;
class SC_TEST;
struct SC_TESTDefaultTypeInternal;
extern SC_TESTDefaultTypeInternal _SC_TEST_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::BuffData* Arena::CreateMaybeMessage<::Protocol::BuffData>(Arena*);
template<> ::Protocol::CS_TEST* Arena::CreateMaybeMessage<::Protocol::CS_TEST>(Arena*);
template<> ::Protocol::SC_TEST* Arena::CreateMaybeMessage<::Protocol::SC_TEST>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class BuffData final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.BuffData) */ {
 public:
  inline BuffData() : BuffData(nullptr) {}
  ~BuffData() override;
  explicit constexpr BuffData(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  BuffData(const BuffData& from);
  BuffData(BuffData&& from) noexcept
    : BuffData() {
    *this = ::std::move(from);
  }

  inline BuffData& operator=(const BuffData& from) {
    CopyFrom(from);
    return *this;
  }
  inline BuffData& operator=(BuffData&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const BuffData& default_instance() {
    return *internal_default_instance();
  }
  static inline const BuffData* internal_default_instance() {
    return reinterpret_cast<const BuffData*>(
               &_BuffData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(BuffData& a, BuffData& b) {
    a.Swap(&b);
  }
  inline void Swap(BuffData* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(BuffData* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline BuffData* New() const final {
    return new BuffData();
  }

  BuffData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<BuffData>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const BuffData& from);
  void MergeFrom(const BuffData& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(BuffData* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.BuffData";
  }
  protected:
  explicit BuffData(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kVictimsFieldNumber = 3,
    kBuffIdFieldNumber = 1,
    kRemainTimeFieldNumber = 2,
  };
  // repeated uint64 victims = 3;
  int victims_size() const;
  private:
  int _internal_victims_size() const;
  public:
  void clear_victims();
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_victims(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 >&
      _internal_victims() const;
  void _internal_add_victims(::PROTOBUF_NAMESPACE_ID::uint64 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 >*
      _internal_mutable_victims();
  public:
  ::PROTOBUF_NAMESPACE_ID::uint64 victims(int index) const;
  void set_victims(int index, ::PROTOBUF_NAMESPACE_ID::uint64 value);
  void add_victims(::PROTOBUF_NAMESPACE_ID::uint64 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 >&
      victims() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 >*
      mutable_victims();

  // uint64 buffId = 1;
  void clear_buffid();
  ::PROTOBUF_NAMESPACE_ID::uint64 buffid() const;
  void set_buffid(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_buffid() const;
  void _internal_set_buffid(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // float remainTime = 2;
  void clear_remaintime();
  float remaintime() const;
  void set_remaintime(float value);
  private:
  float _internal_remaintime() const;
  void _internal_set_remaintime(float value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.BuffData)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 > victims_;
  mutable std::atomic<int> _victims_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::uint64 buffid_;
  float remaintime_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocol_2eproto;
};
// -------------------------------------------------------------------

class SC_TEST final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.SC_TEST) */ {
 public:
  inline SC_TEST() : SC_TEST(nullptr) {}
  ~SC_TEST() override;
  explicit constexpr SC_TEST(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SC_TEST(const SC_TEST& from);
  SC_TEST(SC_TEST&& from) noexcept
    : SC_TEST() {
    *this = ::std::move(from);
  }

  inline SC_TEST& operator=(const SC_TEST& from) {
    CopyFrom(from);
    return *this;
  }
  inline SC_TEST& operator=(SC_TEST&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SC_TEST& default_instance() {
    return *internal_default_instance();
  }
  static inline const SC_TEST* internal_default_instance() {
    return reinterpret_cast<const SC_TEST*>(
               &_SC_TEST_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(SC_TEST& a, SC_TEST& b) {
    a.Swap(&b);
  }
  inline void Swap(SC_TEST* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SC_TEST* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SC_TEST* New() const final {
    return new SC_TEST();
  }

  SC_TEST* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SC_TEST>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SC_TEST& from);
  void MergeFrom(const SC_TEST& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SC_TEST* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.SC_TEST";
  }
  protected:
  explicit SC_TEST(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBuffFieldNumber = 4,
    kIdFieldNumber = 1,
    kHpFieldNumber = 2,
    kAttackFieldNumber = 3,
  };
  // repeated .Protocol.BuffData buff = 4;
  int buff_size() const;
  private:
  int _internal_buff_size() const;
  public:
  void clear_buff();
  ::Protocol::BuffData* mutable_buff(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >*
      mutable_buff();
  private:
  const ::Protocol::BuffData& _internal_buff(int index) const;
  ::Protocol::BuffData* _internal_add_buff();
  public:
  const ::Protocol::BuffData& buff(int index) const;
  ::Protocol::BuffData* add_buff();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >&
      buff() const;

  // uint64 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // uint32 hp = 2;
  void clear_hp();
  ::PROTOBUF_NAMESPACE_ID::uint32 hp() const;
  void set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_hp() const;
  void _internal_set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 attack = 3;
  void clear_attack();
  ::PROTOBUF_NAMESPACE_ID::uint32 attack() const;
  void set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_attack() const;
  void _internal_set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.SC_TEST)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData > buff_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  ::PROTOBUF_NAMESPACE_ID::uint32 hp_;
  ::PROTOBUF_NAMESPACE_ID::uint32 attack_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocol_2eproto;
};
// -------------------------------------------------------------------

class CS_TEST final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.CS_TEST) */ {
 public:
  inline CS_TEST() : CS_TEST(nullptr) {}
  ~CS_TEST() override;
  explicit constexpr CS_TEST(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CS_TEST(const CS_TEST& from);
  CS_TEST(CS_TEST&& from) noexcept
    : CS_TEST() {
    *this = ::std::move(from);
  }

  inline CS_TEST& operator=(const CS_TEST& from) {
    CopyFrom(from);
    return *this;
  }
  inline CS_TEST& operator=(CS_TEST&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const CS_TEST& default_instance() {
    return *internal_default_instance();
  }
  static inline const CS_TEST* internal_default_instance() {
    return reinterpret_cast<const CS_TEST*>(
               &_CS_TEST_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(CS_TEST& a, CS_TEST& b) {
    a.Swap(&b);
  }
  inline void Swap(CS_TEST* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(CS_TEST* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline CS_TEST* New() const final {
    return new CS_TEST();
  }

  CS_TEST* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<CS_TEST>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const CS_TEST& from);
  void MergeFrom(const CS_TEST& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CS_TEST* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.CS_TEST";
  }
  protected:
  explicit CS_TEST(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBuffFieldNumber = 4,
    kIdFieldNumber = 1,
    kHpFieldNumber = 2,
    kAttackFieldNumber = 3,
  };
  // repeated .Protocol.BuffData buff = 4;
  int buff_size() const;
  private:
  int _internal_buff_size() const;
  public:
  void clear_buff();
  ::Protocol::BuffData* mutable_buff(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >*
      mutable_buff();
  private:
  const ::Protocol::BuffData& _internal_buff(int index) const;
  ::Protocol::BuffData* _internal_add_buff();
  public:
  const ::Protocol::BuffData& buff(int index) const;
  ::Protocol::BuffData* add_buff();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >&
      buff() const;

  // uint64 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // uint32 hp = 2;
  void clear_hp();
  ::PROTOBUF_NAMESPACE_ID::uint32 hp() const;
  void set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_hp() const;
  void _internal_set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 attack = 3;
  void clear_attack();
  ::PROTOBUF_NAMESPACE_ID::uint32 attack() const;
  void set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_attack() const;
  void _internal_set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.CS_TEST)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData > buff_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  ::PROTOBUF_NAMESPACE_ID::uint32 hp_;
  ::PROTOBUF_NAMESPACE_ID::uint32 attack_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocol_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// BuffData

// uint64 buffId = 1;
inline void BuffData::clear_buffid() {
  buffid_ = uint64_t{0u};
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 BuffData::_internal_buffid() const {
  return buffid_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 BuffData::buffid() const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.buffId)
  return _internal_buffid();
}
inline void BuffData::_internal_set_buffid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  buffid_ = value;
}
inline void BuffData::set_buffid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_buffid(value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.buffId)
}

// float remainTime = 2;
inline void BuffData::clear_remaintime() {
  remaintime_ = 0;
}
inline float BuffData::_internal_remaintime() const {
  return remaintime_;
}
inline float BuffData::remaintime() const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.remainTime)
  return _internal_remaintime();
}
inline void BuffData::_internal_set_remaintime(float value) {
  
  remaintime_ = value;
}
inline void BuffData::set_remaintime(float value) {
  _internal_set_remaintime(value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.remainTime)
}

// repeated uint64 victims = 3;
inline int BuffData::_internal_victims_size() const {
  return victims_.size();
}
inline int BuffData::victims_size() const {
  return _internal_victims_size();
}
inline void BuffData::clear_victims() {
  victims_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 BuffData::_internal_victims(int index) const {
  return victims_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 BuffData::victims(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.victims)
  return _internal_victims(index);
}
inline void BuffData::set_victims(int index, ::PROTOBUF_NAMESPACE_ID::uint64 value) {
  victims_.Set(index, value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.victims)
}
inline void BuffData::_internal_add_victims(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  victims_.Add(value);
}
inline void BuffData::add_victims(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_add_victims(value);
  // @@protoc_insertion_point(field_add:Protocol.BuffData.victims)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 >&
BuffData::_internal_victims() const {
  return victims_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 >&
BuffData::victims() const {
  // @@protoc_insertion_point(field_list:Protocol.BuffData.victims)
  return _internal_victims();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 >*
BuffData::_internal_mutable_victims() {
  return &victims_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint64 >*
BuffData::mutable_victims() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.BuffData.victims)
  return _internal_mutable_victims();
}

// -------------------------------------------------------------------

// SC_TEST

// uint64 id = 1;
inline void SC_TEST::clear_id() {
  id_ = uint64_t{0u};
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 SC_TEST::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 SC_TEST::id() const {
  // @@protoc_insertion_point(field_get:Protocol.SC_TEST.id)
  return _internal_id();
}
inline void SC_TEST::_internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
}
inline void SC_TEST::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:Protocol.SC_TEST.id)
}

// uint32 hp = 2;
inline void SC_TEST::clear_hp() {
  hp_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SC_TEST::_internal_hp() const {
  return hp_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SC_TEST::hp() const {
  // @@protoc_insertion_point(field_get:Protocol.SC_TEST.hp)
  return _internal_hp();
}
inline void SC_TEST::_internal_set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  hp_ = value;
}
inline void SC_TEST::set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_hp(value);
  // @@protoc_insertion_point(field_set:Protocol.SC_TEST.hp)
}

// uint32 attack = 3;
inline void SC_TEST::clear_attack() {
  attack_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SC_TEST::_internal_attack() const {
  return attack_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SC_TEST::attack() const {
  // @@protoc_insertion_point(field_get:Protocol.SC_TEST.attack)
  return _internal_attack();
}
inline void SC_TEST::_internal_set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  attack_ = value;
}
inline void SC_TEST::set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_attack(value);
  // @@protoc_insertion_point(field_set:Protocol.SC_TEST.attack)
}

// repeated .Protocol.BuffData buff = 4;
inline int SC_TEST::_internal_buff_size() const {
  return buff_.size();
}
inline int SC_TEST::buff_size() const {
  return _internal_buff_size();
}
inline void SC_TEST::clear_buff() {
  buff_.Clear();
}
inline ::Protocol::BuffData* SC_TEST::mutable_buff(int index) {
  // @@protoc_insertion_point(field_mutable:Protocol.SC_TEST.buff)
  return buff_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >*
SC_TEST::mutable_buff() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.SC_TEST.buff)
  return &buff_;
}
inline const ::Protocol::BuffData& SC_TEST::_internal_buff(int index) const {
  return buff_.Get(index);
}
inline const ::Protocol::BuffData& SC_TEST::buff(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.SC_TEST.buff)
  return _internal_buff(index);
}
inline ::Protocol::BuffData* SC_TEST::_internal_add_buff() {
  return buff_.Add();
}
inline ::Protocol::BuffData* SC_TEST::add_buff() {
  // @@protoc_insertion_point(field_add:Protocol.SC_TEST.buff)
  return _internal_add_buff();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >&
SC_TEST::buff() const {
  // @@protoc_insertion_point(field_list:Protocol.SC_TEST.buff)
  return buff_;
}

// -------------------------------------------------------------------

// CS_TEST

// uint64 id = 1;
inline void CS_TEST::clear_id() {
  id_ = uint64_t{0u};
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 CS_TEST::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 CS_TEST::id() const {
  // @@protoc_insertion_point(field_get:Protocol.CS_TEST.id)
  return _internal_id();
}
inline void CS_TEST::_internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
}
inline void CS_TEST::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:Protocol.CS_TEST.id)
}

// uint32 hp = 2;
inline void CS_TEST::clear_hp() {
  hp_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 CS_TEST::_internal_hp() const {
  return hp_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 CS_TEST::hp() const {
  // @@protoc_insertion_point(field_get:Protocol.CS_TEST.hp)
  return _internal_hp();
}
inline void CS_TEST::_internal_set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  hp_ = value;
}
inline void CS_TEST::set_hp(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_hp(value);
  // @@protoc_insertion_point(field_set:Protocol.CS_TEST.hp)
}

// uint32 attack = 3;
inline void CS_TEST::clear_attack() {
  attack_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 CS_TEST::_internal_attack() const {
  return attack_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 CS_TEST::attack() const {
  // @@protoc_insertion_point(field_get:Protocol.CS_TEST.attack)
  return _internal_attack();
}
inline void CS_TEST::_internal_set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  attack_ = value;
}
inline void CS_TEST::set_attack(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_attack(value);
  // @@protoc_insertion_point(field_set:Protocol.CS_TEST.attack)
}

// repeated .Protocol.BuffData buff = 4;
inline int CS_TEST::_internal_buff_size() const {
  return buff_.size();
}
inline int CS_TEST::buff_size() const {
  return _internal_buff_size();
}
inline void CS_TEST::clear_buff() {
  buff_.Clear();
}
inline ::Protocol::BuffData* CS_TEST::mutable_buff(int index) {
  // @@protoc_insertion_point(field_mutable:Protocol.CS_TEST.buff)
  return buff_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >*
CS_TEST::mutable_buff() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.CS_TEST.buff)
  return &buff_;
}
inline const ::Protocol::BuffData& CS_TEST::_internal_buff(int index) const {
  return buff_.Get(index);
}
inline const ::Protocol::BuffData& CS_TEST::buff(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.CS_TEST.buff)
  return _internal_buff(index);
}
inline ::Protocol::BuffData* CS_TEST::_internal_add_buff() {
  return buff_.Add();
}
inline ::Protocol::BuffData* CS_TEST::add_buff() {
  // @@protoc_insertion_point(field_add:Protocol.CS_TEST.buff)
  return _internal_add_buff();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >&
CS_TEST::buff() const {
  // @@protoc_insertion_point(field_list:Protocol.CS_TEST.buff)
  return buff_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto
