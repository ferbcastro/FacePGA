#include "neural/net/module.hpp"
#include "neural/net/layers.hpp"
#include "neural/net/activations.hpp"

#include "neural/func/loss.hpp"
#include "neural/func/optimizer.hpp"

#include "utils/logger.hpp"

class ShallowCnn : public Module { };

// Knobs:
// export folder
// dataset source
// path to model architecture
// path to hyperparameters config file

// Stages:
// 1. Process knobs
// 2. Build model
// 3. Load dataset
// 4. Train models and select best one
// 5. Export model
int main(int argc, char* argv[]) {
    return 0;
}