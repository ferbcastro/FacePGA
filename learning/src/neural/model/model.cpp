#include "model.hpp"

/**
 * @file model.cpp
 */

int Model::OpenDataset(const char* path) {
    (void)path;
    return 0;
}

int Model::OpenArchFile(const char* path) {
    (void)path;
    return 0;
}

int Model::OpenParamsFile(const char* path) {
    (void)path;
    return 0;
}

int Model::TrainAndSelectBest() {
    return 0;
}

int Model::Export() const {
    return serial.ExportModel(this);
}

int Serializer::ExportModel(const Model* model) const {
    (void)model;
    return 0;
}