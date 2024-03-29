// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Struct.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Struct_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Struct_2eproto

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
#include "Enum.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Struct_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Struct_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Struct_2eproto;
namespace Protocol {
class Packet_ChannelInfo;
struct Packet_ChannelInfoDefaultTypeInternal;
extern Packet_ChannelInfoDefaultTypeInternal _Packet_ChannelInfo_default_instance_;
class Packet_CharacterInfo;
struct Packet_CharacterInfoDefaultTypeInternal;
extern Packet_CharacterInfoDefaultTypeInternal _Packet_CharacterInfo_default_instance_;
class Packet_Vector;
struct Packet_VectorDefaultTypeInternal;
extern Packet_VectorDefaultTypeInternal _Packet_Vector_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::Packet_ChannelInfo* Arena::CreateMaybeMessage<::Protocol::Packet_ChannelInfo>(Arena*);
template<> ::Protocol::Packet_CharacterInfo* Arena::CreateMaybeMessage<::Protocol::Packet_CharacterInfo>(Arena*);
template<> ::Protocol::Packet_Vector* Arena::CreateMaybeMessage<::Protocol::Packet_Vector>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class Packet_Vector final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.Packet_Vector) */ {
 public:
  inline Packet_Vector() : Packet_Vector(nullptr) {}
  ~Packet_Vector() override;
  explicit constexpr Packet_Vector(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Packet_Vector(const Packet_Vector& from);
  Packet_Vector(Packet_Vector&& from) noexcept
    : Packet_Vector() {
    *this = ::std::move(from);
  }

  inline Packet_Vector& operator=(const Packet_Vector& from) {
    CopyFrom(from);
    return *this;
  }
  inline Packet_Vector& operator=(Packet_Vector&& from) noexcept {
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
  static const Packet_Vector& default_instance() {
    return *internal_default_instance();
  }
  static inline const Packet_Vector* internal_default_instance() {
    return reinterpret_cast<const Packet_Vector*>(
               &_Packet_Vector_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Packet_Vector& a, Packet_Vector& b) {
    a.Swap(&b);
  }
  inline void Swap(Packet_Vector* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Packet_Vector* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Packet_Vector* New() const final {
    return new Packet_Vector();
  }

  Packet_Vector* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Packet_Vector>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Packet_Vector& from);
  void MergeFrom(const Packet_Vector& from);
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
  void InternalSwap(Packet_Vector* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Packet_Vector";
  }
  protected:
  explicit Packet_Vector(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kXFieldNumber = 1,
    kYFieldNumber = 2,
  };
  // int64 x = 1;
  void clear_x();
  ::PROTOBUF_NAMESPACE_ID::int64 x() const;
  void set_x(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_x() const;
  void _internal_set_x(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // int64 y = 2;
  void clear_y();
  ::PROTOBUF_NAMESPACE_ID::int64 y() const;
  void set_y(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_y() const;
  void _internal_set_y(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.Packet_Vector)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::int64 x_;
  ::PROTOBUF_NAMESPACE_ID::int64 y_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Struct_2eproto;
};
// -------------------------------------------------------------------

class Packet_CharacterInfo final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.Packet_CharacterInfo) */ {
 public:
  inline Packet_CharacterInfo() : Packet_CharacterInfo(nullptr) {}
  ~Packet_CharacterInfo() override;
  explicit constexpr Packet_CharacterInfo(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Packet_CharacterInfo(const Packet_CharacterInfo& from);
  Packet_CharacterInfo(Packet_CharacterInfo&& from) noexcept
    : Packet_CharacterInfo() {
    *this = ::std::move(from);
  }

  inline Packet_CharacterInfo& operator=(const Packet_CharacterInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline Packet_CharacterInfo& operator=(Packet_CharacterInfo&& from) noexcept {
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
  static const Packet_CharacterInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const Packet_CharacterInfo* internal_default_instance() {
    return reinterpret_cast<const Packet_CharacterInfo*>(
               &_Packet_CharacterInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Packet_CharacterInfo& a, Packet_CharacterInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(Packet_CharacterInfo* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Packet_CharacterInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Packet_CharacterInfo* New() const final {
    return new Packet_CharacterInfo();
  }

  Packet_CharacterInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Packet_CharacterInfo>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Packet_CharacterInfo& from);
  void MergeFrom(const Packet_CharacterInfo& from);
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
  void InternalSwap(Packet_CharacterInfo* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Packet_CharacterInfo";
  }
  protected:
  explicit Packet_CharacterInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 16,
    kIdFieldNumber = 1,
    kPlayerTypeFieldNumber = 2,
  };
  // repeated int32 name = 16;
  int name_size() const;
  private:
  int _internal_name_size() const;
  public:
  void clear_name();
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_name(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      _internal_name() const;
  void _internal_add_name(::PROTOBUF_NAMESPACE_ID::int32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      _internal_mutable_name();
  public:
  ::PROTOBUF_NAMESPACE_ID::int32 name(int index) const;
  void set_name(int index, ::PROTOBUF_NAMESPACE_ID::int32 value);
  void add_name(::PROTOBUF_NAMESPACE_ID::int32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      name() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      mutable_name();

  // uint64 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // .Protocol.PlayerType playerType = 2;
  void clear_playertype();
  ::Protocol::PlayerType playertype() const;
  void set_playertype(::Protocol::PlayerType value);
  private:
  ::Protocol::PlayerType _internal_playertype() const;
  void _internal_set_playertype(::Protocol::PlayerType value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.Packet_CharacterInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 > name_;
  mutable std::atomic<int> _name_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  int playertype_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Struct_2eproto;
};
// -------------------------------------------------------------------

class Packet_ChannelInfo final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.Packet_ChannelInfo) */ {
 public:
  inline Packet_ChannelInfo() : Packet_ChannelInfo(nullptr) {}
  ~Packet_ChannelInfo() override;
  explicit constexpr Packet_ChannelInfo(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Packet_ChannelInfo(const Packet_ChannelInfo& from);
  Packet_ChannelInfo(Packet_ChannelInfo&& from) noexcept
    : Packet_ChannelInfo() {
    *this = ::std::move(from);
  }

  inline Packet_ChannelInfo& operator=(const Packet_ChannelInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline Packet_ChannelInfo& operator=(Packet_ChannelInfo&& from) noexcept {
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
  static const Packet_ChannelInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const Packet_ChannelInfo* internal_default_instance() {
    return reinterpret_cast<const Packet_ChannelInfo*>(
               &_Packet_ChannelInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(Packet_ChannelInfo& a, Packet_ChannelInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(Packet_ChannelInfo* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Packet_ChannelInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Packet_ChannelInfo* New() const final {
    return new Packet_ChannelInfo();
  }

  Packet_ChannelInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Packet_ChannelInfo>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Packet_ChannelInfo& from);
  void MergeFrom(const Packet_ChannelInfo& from);
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
  void InternalSwap(Packet_ChannelInfo* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Packet_ChannelInfo";
  }
  protected:
  explicit Packet_ChannelInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kChannelNameFieldNumber = 16,
    kChannelIDFieldNumber = 1,
    kMaxChannelUserFieldNumber = 2,
    kUserCountsFieldNumber = 3,
  };
  // repeated int32 channelName = 16;
  int channelname_size() const;
  private:
  int _internal_channelname_size() const;
  public:
  void clear_channelname();
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_channelname(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      _internal_channelname() const;
  void _internal_add_channelname(::PROTOBUF_NAMESPACE_ID::int32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      _internal_mutable_channelname();
  public:
  ::PROTOBUF_NAMESPACE_ID::int32 channelname(int index) const;
  void set_channelname(int index, ::PROTOBUF_NAMESPACE_ID::int32 value);
  void add_channelname(::PROTOBUF_NAMESPACE_ID::int32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      channelname() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      mutable_channelname();

  // uint32 channelID = 1;
  void clear_channelid();
  ::PROTOBUF_NAMESPACE_ID::uint32 channelid() const;
  void set_channelid(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_channelid() const;
  void _internal_set_channelid(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 maxChannelUser = 2;
  void clear_maxchanneluser();
  ::PROTOBUF_NAMESPACE_ID::uint32 maxchanneluser() const;
  void set_maxchanneluser(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_maxchanneluser() const;
  void _internal_set_maxchanneluser(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 userCounts = 3;
  void clear_usercounts();
  ::PROTOBUF_NAMESPACE_ID::uint32 usercounts() const;
  void set_usercounts(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_usercounts() const;
  void _internal_set_usercounts(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.Packet_ChannelInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 > channelname_;
  mutable std::atomic<int> _channelname_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 channelid_;
  ::PROTOBUF_NAMESPACE_ID::uint32 maxchanneluser_;
  ::PROTOBUF_NAMESPACE_ID::uint32 usercounts_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Struct_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Packet_Vector

// int64 x = 1;
inline void Packet_Vector::clear_x() {
  x_ = int64_t{0};
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Packet_Vector::_internal_x() const {
  return x_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Packet_Vector::x() const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_Vector.x)
  return _internal_x();
}
inline void Packet_Vector::_internal_set_x(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  x_ = value;
}
inline void Packet_Vector::set_x(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_x(value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_Vector.x)
}

// int64 y = 2;
inline void Packet_Vector::clear_y() {
  y_ = int64_t{0};
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Packet_Vector::_internal_y() const {
  return y_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Packet_Vector::y() const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_Vector.y)
  return _internal_y();
}
inline void Packet_Vector::_internal_set_y(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  y_ = value;
}
inline void Packet_Vector::set_y(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_y(value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_Vector.y)
}

// -------------------------------------------------------------------

// Packet_CharacterInfo

// uint64 id = 1;
inline void Packet_CharacterInfo::clear_id() {
  id_ = uint64_t{0u};
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Packet_CharacterInfo::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Packet_CharacterInfo::id() const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_CharacterInfo.id)
  return _internal_id();
}
inline void Packet_CharacterInfo::_internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
}
inline void Packet_CharacterInfo::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_CharacterInfo.id)
}

// .Protocol.PlayerType playerType = 2;
inline void Packet_CharacterInfo::clear_playertype() {
  playertype_ = 0;
}
inline ::Protocol::PlayerType Packet_CharacterInfo::_internal_playertype() const {
  return static_cast< ::Protocol::PlayerType >(playertype_);
}
inline ::Protocol::PlayerType Packet_CharacterInfo::playertype() const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_CharacterInfo.playerType)
  return _internal_playertype();
}
inline void Packet_CharacterInfo::_internal_set_playertype(::Protocol::PlayerType value) {
  
  playertype_ = value;
}
inline void Packet_CharacterInfo::set_playertype(::Protocol::PlayerType value) {
  _internal_set_playertype(value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_CharacterInfo.playerType)
}

// repeated int32 name = 16;
inline int Packet_CharacterInfo::_internal_name_size() const {
  return name_.size();
}
inline int Packet_CharacterInfo::name_size() const {
  return _internal_name_size();
}
inline void Packet_CharacterInfo::clear_name() {
  name_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Packet_CharacterInfo::_internal_name(int index) const {
  return name_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Packet_CharacterInfo::name(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_CharacterInfo.name)
  return _internal_name(index);
}
inline void Packet_CharacterInfo::set_name(int index, ::PROTOBUF_NAMESPACE_ID::int32 value) {
  name_.Set(index, value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_CharacterInfo.name)
}
inline void Packet_CharacterInfo::_internal_add_name(::PROTOBUF_NAMESPACE_ID::int32 value) {
  name_.Add(value);
}
inline void Packet_CharacterInfo::add_name(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_add_name(value);
  // @@protoc_insertion_point(field_add:Protocol.Packet_CharacterInfo.name)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
Packet_CharacterInfo::_internal_name() const {
  return name_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
Packet_CharacterInfo::name() const {
  // @@protoc_insertion_point(field_list:Protocol.Packet_CharacterInfo.name)
  return _internal_name();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
Packet_CharacterInfo::_internal_mutable_name() {
  return &name_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
Packet_CharacterInfo::mutable_name() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.Packet_CharacterInfo.name)
  return _internal_mutable_name();
}

// -------------------------------------------------------------------

// Packet_ChannelInfo

// uint32 channelID = 1;
inline void Packet_ChannelInfo::clear_channelid() {
  channelid_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Packet_ChannelInfo::_internal_channelid() const {
  return channelid_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Packet_ChannelInfo::channelid() const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_ChannelInfo.channelID)
  return _internal_channelid();
}
inline void Packet_ChannelInfo::_internal_set_channelid(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  channelid_ = value;
}
inline void Packet_ChannelInfo::set_channelid(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_channelid(value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_ChannelInfo.channelID)
}

// uint32 maxChannelUser = 2;
inline void Packet_ChannelInfo::clear_maxchanneluser() {
  maxchanneluser_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Packet_ChannelInfo::_internal_maxchanneluser() const {
  return maxchanneluser_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Packet_ChannelInfo::maxchanneluser() const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_ChannelInfo.maxChannelUser)
  return _internal_maxchanneluser();
}
inline void Packet_ChannelInfo::_internal_set_maxchanneluser(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  maxchanneluser_ = value;
}
inline void Packet_ChannelInfo::set_maxchanneluser(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_maxchanneluser(value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_ChannelInfo.maxChannelUser)
}

// uint32 userCounts = 3;
inline void Packet_ChannelInfo::clear_usercounts() {
  usercounts_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Packet_ChannelInfo::_internal_usercounts() const {
  return usercounts_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Packet_ChannelInfo::usercounts() const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_ChannelInfo.userCounts)
  return _internal_usercounts();
}
inline void Packet_ChannelInfo::_internal_set_usercounts(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  usercounts_ = value;
}
inline void Packet_ChannelInfo::set_usercounts(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_usercounts(value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_ChannelInfo.userCounts)
}

// repeated int32 channelName = 16;
inline int Packet_ChannelInfo::_internal_channelname_size() const {
  return channelname_.size();
}
inline int Packet_ChannelInfo::channelname_size() const {
  return _internal_channelname_size();
}
inline void Packet_ChannelInfo::clear_channelname() {
  channelname_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Packet_ChannelInfo::_internal_channelname(int index) const {
  return channelname_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Packet_ChannelInfo::channelname(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.Packet_ChannelInfo.channelName)
  return _internal_channelname(index);
}
inline void Packet_ChannelInfo::set_channelname(int index, ::PROTOBUF_NAMESPACE_ID::int32 value) {
  channelname_.Set(index, value);
  // @@protoc_insertion_point(field_set:Protocol.Packet_ChannelInfo.channelName)
}
inline void Packet_ChannelInfo::_internal_add_channelname(::PROTOBUF_NAMESPACE_ID::int32 value) {
  channelname_.Add(value);
}
inline void Packet_ChannelInfo::add_channelname(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_add_channelname(value);
  // @@protoc_insertion_point(field_add:Protocol.Packet_ChannelInfo.channelName)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
Packet_ChannelInfo::_internal_channelname() const {
  return channelname_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
Packet_ChannelInfo::channelname() const {
  // @@protoc_insertion_point(field_list:Protocol.Packet_ChannelInfo.channelName)
  return _internal_channelname();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
Packet_ChannelInfo::_internal_mutable_channelname() {
  return &channelname_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
Packet_ChannelInfo::mutable_channelname() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.Packet_ChannelInfo.channelName)
  return _internal_mutable_channelname();
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
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Struct_2eproto
