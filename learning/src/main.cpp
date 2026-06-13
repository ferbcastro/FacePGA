#include <cstddef>

extern "C" {
#include <getopt.h>
}

#include "utils/logger.hpp"
#include "shallow.hpp"

void Usage () {
    printf("========================================\n");
    printf("FacePGA Learning - Usage\n");
    printf("========================================\n");
    printf("Required parameters:\n");
    printf("  -d <file>   Path to the dataset file\n");
    printf("  -a <file>   Path to the model architecture file\n");
    printf("  -h <file>   Path to the hyperparameters file\n");
    printf("Optional parameters:\n");
    printf("  -e <dir>    Directory to export results (default: current directory)\n");
    printf("\nExample:\n");
    printf("  ./facepga -d dataset.csv -a arch.json -h hyper.json -e ./results\n");
    printf("========================================\n");
}

int main(int argc, char* argv[]) {
    const char* options = "e:d:a:h:";
    char opt;

    const char* exportTo = ".";
    const char* datasetPath = NULL;
    const char* archPath = NULL;
    const char* paramsPath = NULL;

    while((opt = getopt(argc, argv, options)) != -1) {
      switch (opt) {
        case 'e':
            exportTo = optarg;
            FACEPGA_DEBUG_PRINTF("Exporting to [%s]\n", exportTo);
            break;
        case 'd':
            datasetPath = optarg;
            FACEPGA_DEBUG_PRINTF("Dataset from [%s]\n", datasetPath);
            break;
        case 'a':
            archPath = optarg;
            FACEPGA_DEBUG_PRINTF("Architecture from [%s]\n", archPath);
            break;
        case 'h':
            paramsPath = optarg;
            FACEPGA_DEBUG_PRINTF("Hyperparameters from [%s]\n", paramsPath);
            break;
        default:
            FACEPGA_WARNING_PRINTF("Invalid option argument!\n");
            break;
      }
    }

    if (!datasetPath || !archPath || !paramsPath) {
        FACEPGA_ERROR_PRINTF("Required parameter left unset!\n\n");
        Usage();
        return 1;
    }

    int ret;

    ShallowCnn cnn;

    if (cnn.OpenDataset(datasetPath)) {
        FACEPGA_ERROR_PRINTF("Failed to open dataset!\n");
        return 1;
    }
    if (cnn.OpenArchFile(archPath)) {
        FACEPGA_ERROR_PRINTF("Failed to open model arch file!\n");
        return 1;
    }
    if (cnn.OpenParamsFile(paramsPath)) {
        FACEPGA_ERROR_PRINTF("Failed to open hyperparameters file!\n");
        return 1;
    }

    ret = cnn.TrainAndSelectBest();
    assert(ret == 0);
    ret = cnn.Export();
    assert(ret == 0);

    return 0;
}