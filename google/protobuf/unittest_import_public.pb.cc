// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_import_public.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include <google/protobuf/unittest_import_public.pb.h>

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace protobuf_unittest_import {
class PublicImportMessageDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<PublicImportMessage> {};
PublicImportMessageDefaultTypeInternal _PublicImportMessage_default_instance_;

namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace


const ::google::protobuf::uint32* protobuf_Offsets_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto() GOOGLE_ATTRIBUTE_COLD;
const ::google::protobuf::uint32* protobuf_Offsets_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto() {
  static const ::google::protobuf::uint32 offsets[] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PublicImportMessage, _has_bits_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PublicImportMessage, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PublicImportMessage, e_),
    0,
  };
  return offsets;
}

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 5, sizeof(PublicImportMessage)},
};

static const ::google::protobuf::internal::DefaultInstanceData file_default_instances[] = {
  {reinterpret_cast<const ::google::protobuf::Message*>(&_PublicImportMessage_default_instance_), NULL},
};

namespace {

void protobuf_AssignDescriptors() {
  protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "google/protobuf/unittest_import_public.proto", schemas, file_default_instances, protobuf_Offsets_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto(), factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace

void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto() {
  _PublicImportMessage_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void protobuf_InitDefaults_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _PublicImportMessage_default_instance_.DefaultConstruct();
}

void protobuf_InitDefaults_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_InitDefaults_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_impl);
}
void protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_impl() {
  protobuf_InitDefaults_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto();
  static const char descriptor[] = {
      "\n,google/protobuf/unittest_import_public"
      ".proto\022\030protobuf_unittest_import\" \n\023Publ"
      "icImportMessage\022\t\n\001e\030\001 \001(\005B\032\n\030com.google"
      ".protobuf.test"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 134);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "google/protobuf/unittest_import_public.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_once_);
void protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_once_,
                 &protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto {
  StaticDescriptorInitializer_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto() {
    protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto();
  }
} static_descriptor_initializer_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PublicImportMessage::kEFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PublicImportMessage::PublicImportMessage()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_InitDefaults_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:protobuf_unittest_import.PublicImportMessage)
}
PublicImportMessage::PublicImportMessage(const PublicImportMessage& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  e_ = from.e_;
  // @@protoc_insertion_point(copy_constructor:protobuf_unittest_import.PublicImportMessage)
}

void PublicImportMessage::SharedCtor() {
  _cached_size_ = 0;
  e_ = 0;
}

PublicImportMessage::~PublicImportMessage() {
  // @@protoc_insertion_point(destructor:protobuf_unittest_import.PublicImportMessage)
  SharedDtor();
}

void PublicImportMessage::SharedDtor() {
}

void PublicImportMessage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PublicImportMessage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[0].descriptor;
}

const PublicImportMessage& PublicImportMessage::default_instance() {
  protobuf_InitDefaults_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto();
  return *internal_default_instance();
}

PublicImportMessage* PublicImportMessage::New(::google::protobuf::Arena* arena) const {
  PublicImportMessage* n = new PublicImportMessage;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void PublicImportMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest_import.PublicImportMessage)
  e_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool PublicImportMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:protobuf_unittest_import.PublicImportMessage)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 e = 1;
      case 1: {
        if (tag == 8u) {
          set_has_e();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &e_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:protobuf_unittest_import.PublicImportMessage)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:protobuf_unittest_import.PublicImportMessage)
  return false;
#undef DO_
}

void PublicImportMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:protobuf_unittest_import.PublicImportMessage)
  // optional int32 e = 1;
  if (has_e()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->e(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:protobuf_unittest_import.PublicImportMessage)
}

::google::protobuf::uint8* PublicImportMessage::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:protobuf_unittest_import.PublicImportMessage)
  // optional int32 e = 1;
  if (has_e()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->e(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protobuf_unittest_import.PublicImportMessage)
  return target;
}

size_t PublicImportMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest_import.PublicImportMessage)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  // optional int32 e = 1;
  if (has_e()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->e());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void PublicImportMessage::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:protobuf_unittest_import.PublicImportMessage)
  GOOGLE_DCHECK_NE(&from, this);
  const PublicImportMessage* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const PublicImportMessage>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:protobuf_unittest_import.PublicImportMessage)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:protobuf_unittest_import.PublicImportMessage)
    MergeFrom(*source);
  }
}

void PublicImportMessage::MergeFrom(const PublicImportMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest_import.PublicImportMessage)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_e()) {
    set_e(from.e());
  }
}

void PublicImportMessage::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:protobuf_unittest_import.PublicImportMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PublicImportMessage::CopyFrom(const PublicImportMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest_import.PublicImportMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PublicImportMessage::IsInitialized() const {
  return true;
}

void PublicImportMessage::Swap(PublicImportMessage* other) {
  if (other == this) return;
  InternalSwap(other);
}
void PublicImportMessage::InternalSwap(PublicImportMessage* other) {
  std::swap(e_, other->e_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata PublicImportMessage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// PublicImportMessage

// optional int32 e = 1;
bool PublicImportMessage::has_e() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void PublicImportMessage::set_has_e() {
  _has_bits_[0] |= 0x00000001u;
}
void PublicImportMessage::clear_has_e() {
  _has_bits_[0] &= ~0x00000001u;
}
void PublicImportMessage::clear_e() {
  e_ = 0;
  clear_has_e();
}
::google::protobuf::int32 PublicImportMessage::e() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest_import.PublicImportMessage.e)
  return e_;
}
void PublicImportMessage::set_e(::google::protobuf::int32 value) {
  set_has_e();
  e_ = value;
  // @@protoc_insertion_point(field_set:protobuf_unittest_import.PublicImportMessage.e)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_unittest_import

// @@protoc_insertion_point(global_scope)
