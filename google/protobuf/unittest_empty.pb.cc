// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_empty.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include <google/protobuf/unittest_empty.pb.h>

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

namespace {


}  // namespace

inline ::google::protobuf::uint32* protobuf_Offsets_google_2fprotobuf_2funittest_5fempty_2eproto() { return NULL; }
static const ::google::protobuf::internal::MigrationSchema* schemas = NULL;
static const ::google::protobuf::internal::DefaultInstanceData* file_default_instances = NULL;
namespace {

void protobuf_AssignDescriptors() {
  protobuf_AddDesc_google_2fprotobuf_2funittest_5fempty_2eproto();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "google/protobuf/unittest_empty.proto", schemas, file_default_instances, protobuf_Offsets_google_2fprotobuf_2funittest_5fempty_2eproto(), factory,
      NULL, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fempty_2eproto() {
}

void protobuf_InitDefaults_google_2fprotobuf_2funittest_5fempty_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
}

void protobuf_InitDefaults_google_2fprotobuf_2funittest_5fempty_2eproto() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_InitDefaults_google_2fprotobuf_2funittest_5fempty_2eproto_impl);
}
void protobuf_AddDesc_google_2fprotobuf_2funittest_5fempty_2eproto_impl() {
  protobuf_InitDefaults_google_2fprotobuf_2funittest_5fempty_2eproto();
  static const char descriptor[] = {
      "\n$google/protobuf/unittest_empty.proto"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 38);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "google/protobuf/unittest_empty.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fempty_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_google_2fprotobuf_2funittest_5fempty_2eproto_once_);
void protobuf_AddDesc_google_2fprotobuf_2funittest_5fempty_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_google_2fprotobuf_2funittest_5fempty_2eproto_once_,
                 &protobuf_AddDesc_google_2fprotobuf_2funittest_5fempty_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_google_2fprotobuf_2funittest_5fempty_2eproto {
  StaticDescriptorInitializer_google_2fprotobuf_2funittest_5fempty_2eproto() {
    protobuf_AddDesc_google_2fprotobuf_2funittest_5fempty_2eproto();
  }
} static_descriptor_initializer_google_2fprotobuf_2funittest_5fempty_2eproto_;

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
