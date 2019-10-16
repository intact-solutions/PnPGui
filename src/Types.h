#pragma once

#include <string>
#include <vector>
#include <map>
#include <imgui_node_editor.h>

struct Node;

enum class PinType {
  Flow,
  Bool,
  Int,
  Float,
  String,
  Object,
  Function,
  Delegate,
};

enum class PinKind { Output, Input };

struct Pin {
  ax::NodeEditor::PinId ID;
  Node* Node;
  std::string Name;
  PinType Type;
  PinKind Kind;

  Pin(int id, const char* name, PinType type)
    : ID(id), Node(nullptr), Name(name), Type(type), Kind(PinKind::Input) {}
};

static bool CanCreateLink(Pin* a, Pin* b) {
  if (!a || !b || a == b || a->Kind == b->Kind || a->Type != b->Type ||
      a->Node == b->Node)
    return false;

  return true;
}

ImColor GetIconColor(PinType type) {
  switch (type) {
    default:
    case PinType::Flow:
      return ImColor(255, 255, 255);
    case PinType::Bool:
      return ImColor(220, 48, 48);
    case PinType::Int:
      return ImColor(68, 201, 156);
    case PinType::Float:
      return ImColor(147, 226, 74);
    case PinType::String:
      return ImColor(124, 21, 153);
    case PinType::Object:
      return ImColor(51, 150, 215);
    case PinType::Function:
      return ImColor(218, 0, 183);
    case PinType::Delegate:
      return ImColor(255, 48, 48);
  }
};


enum class NodeType { Blueprint, Simple, Tree, Comment };

struct Node;

struct Node {
  ax::NodeEditor::NodeId ID;
  std::string Name;
  std::vector<Pin> Inputs;
  std::vector<Pin> Outputs;
  ImColor Color;
  NodeType Type;
  ImVec2 Size;

  std::string State;
  std::string SavedState;

  Node(int id, const char* name, ImColor color = ImColor(255, 255, 255))
      : ID(id),
        Name(name),
        Color(color),
        Type(NodeType::Blueprint),
        Size(0, 0) {}
};

struct Link {
  ax::NodeEditor::LinkId ID;

  ax::NodeEditor::PinId StartPinID;
  ax::NodeEditor::PinId EndPinID;

  ImColor Color;

  Link(ax::NodeEditor::LinkId id, ax::NodeEditor::PinId startPinId, ax::NodeEditor::PinId endPinId)
      : ID(id),
        StartPinID(startPinId),
        EndPinID(endPinId),
        Color(255, 255, 255) {}
};


