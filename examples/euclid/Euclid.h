#pragma once

#include <cassert>
#include "dagnabbit/Graph.h"
#include "dagnabbit/PassthroughNode.h"
#include "EuclidNode.h"
#include "PulseNode.h"

namespace dc::euclid {
template<class TimeType>
class Euclid : public Graph<TimeType> {
public:
  using DataType = bool;

  Euclid(const TimeType& rateMin,
         const TimeType& rateMax,
         const TimeType& rateDefault,
         const TimeType& rateStep,
         uint8_t defaultSteps,
         uint8_t defaultPulses) : Graph<TimeType>(32, 3) {
    // make the nodes and connect them
    NodeId pulseNodeId, euclidNodeId, outputNodeId;
    auto status = this->addNode(
        [rateMin, rateMax, rateDefault, rateStep, this]() {
          this->_pulseNode = new PulseNode<TimeType, DataType>(rateMin, rateMax, rateDefault, rateStep, true, 1);
          return this->_pulseNode;
        },
        [&pulseNodeId]([[maybe_unused]] Status status, NodeId nodeId) {
          assert(status == Status::Ok);
          assert(nodeId != InvalidNodeId);
          pulseNodeId = nodeId;
        });
    assert(status == Status::Ok);
    status = this->addNode(
        [defaultSteps, defaultPulses, this]() {
          this->_euclidNode = new EuclidNode<TimeType, DataType>(defaultSteps, defaultPulses, 16, 1);
          return this->_euclidNode;
        },
        [&euclidNodeId]([[maybe_unused]] Status status, NodeId nodeId) {
          assert(status == Status::Ok);
          assert(nodeId != InvalidNodeId);
          euclidNodeId = nodeId;
        });
    assert(status == Status::Ok);
    status = this->addNode(
        [this]() {
          this->_outputNode = new PassthroughNode<DataType, TimeType>(16, 0);
          return this->_outputNode;
        },
        [&outputNodeId]([[maybe_unused]] Status status, NodeId nodeId) {
          assert(status == Status::Ok);
          assert(nodeId != InvalidNodeId);
          outputNodeId = nodeId;
        });
    assert(status == Status::Ok);
    status = this->process();
    assert(status == Status::Ok);
    Status internalStatus{Status::Ok};
    status = this->connectNodes(pulseNodeId, 0, euclidNodeId, 0,
                                [&internalStatus](Status status, NodeId, size_t, NodeId, size_t) {
                                  internalStatus = status;
                                });
    assert(status == Status::Ok);
    status = this->process();
    assert(status == Status::Ok);
    assert(internalStatus == Status::Ok);
    status = this->connectNodes(euclidNodeId, 0, outputNodeId, 0,
                                [&internalStatus](Status status, NodeId, size_t, NodeId, size_t) {
                                  internalStatus = status;
                                });
    assert(status == Status::Ok);
    status = this->process();
    assert(status == Status::Ok);
    assert(internalStatus == Status::Ok);
  }

  Status setEnabled(bool enabled) {
    if (_pulseNode == nullptr) {
      return Status::NotInitialized;
    }
    _pulseNode->setEnabled(enabled);
    return Status::Ok;
  }

  Status popOutputMessage(Message<DataType, TimeType>& msg) {
    return _outputNode->popMessage(msg);
  }

private:
  PulseNode<TimeType, DataType>* _pulseNode{nullptr};
  EuclidNode<TimeType, DataType>* _euclidNode{nullptr};
  PassthroughNode<DataType, TimeType>* _outputNode{nullptr};
};
}
