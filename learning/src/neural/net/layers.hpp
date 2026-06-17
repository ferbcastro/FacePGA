#ifndef FACEPGA_LAYERS_HPP_
#define FACEPGA_LAYERS_HPP_

#include "tensor.hpp"

#include <torch/torch.h>

// Forward declaration of Loss interface
class Loss;

class Layer {
  protected:
    Tensor* output;
    Tensor* weights;
    Tensor* biases;

    friend class Loss;
  public:
    Layer() : output(0), weights(0), biases(0) {}

    /** */
    virtual const Tensor* Forward(Tensor* act) = 0;
    /** */
    virtual const Tensor* Backward(Tensor* grad) = 0;
    /** */
    virtual void PrintWeights() = 0;
    /** */
    virtual void PrintBiases() = 0;

    virtual ~Layer() {
        if (output) delete[] output;
        if (weights) delete[] weights;
        if (biases) delete[] biases;
    }
};

enum GroupType {
    GroupTypeStandard = 0
};

enum PaddingType {
    PaddingTypeZeros = 0
};

class Conv : public Layer {
  private:
    int inputChannels;
    int outputChannels;
    int kernelSize;
    int stride;
    int padding;
    int dilation;

    GroupType convType;
    PaddingType paddingType;

    bool hasBias;

  public:
    /** */
    virtual const Tensor* Forward(Tensor* activations) { return 0; }
    /** */
    virtual const Tensor* Backward(Tensor* gradients) { return 0; }
    /** */
    virtual void PrintWeights() {}
    /** */
    virtual void PrintBiases() {}
};

class Pool : public Layer { };

class Dense : public Layer { };

#endif