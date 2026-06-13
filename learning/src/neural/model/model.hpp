#ifndef FACEPGA_UTILS_MODEL_HPP_
#define FACEPGA_UTILS_MODEL_HPP_

/**
 * @file model.hpp
 */

#include "../net/layers.hpp"
#include "../net/activations.hpp"
#include "../func/loss.hpp"
#include "../func/optimizer.hpp"

class Model;

class Serializer {
  private:

  public:
    Serializer() {}

    /** Export the model to a binary file. */
    int ExportModel(const Model* model) const;

    ~Serializer() {}
};

class Model {
  private:
    Serializer serial;
  public:
    Model() {}

    /** Open dataset and configure data loader. */
    int OpenDataset(const char* path);
    /** Open model architecture file and setup model. */
    int OpenArchFile(const char* path);
    /** Open hyperparameters file and configure model. */
    int OpenParamsFile(const char* path);
    /** Train the model and select the best version across epochs. */
    int TrainAndSelectBest();
    /** Export the trained model. */
    int Export() const;

    ~Model() {}
};

#endif