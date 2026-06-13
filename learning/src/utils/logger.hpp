#ifndef FACEPGA_UTILS_LOGGER_HPP_
#define FACEPGA_UTILS_LOGGER_HPP_

/**
 * @file logger.hpp
 */

#include <cassert>
#include <cstdarg>
#include <string>
#include <vector>

namespace logger {
enum Level {
    LevelError = 0,
    LevelWarning = 1,
    LevelInfo = 2,
#ifndef NDEBUG
    LevelDebug = 3,
#endif
};

/**
 * @brief Basic singleton logger with contextual logging support.
 *
 * @details This keeps printf-style formatting to minimize migration effort from
 * the previous macros while adding file, line, and function metadata.
 */
class Logger {
  private:
    /* Minimum level that will be emitted. Messages with level > minLevel
     * are filtered out. */
    Level minLevel;

    /* List of basenames to filter by (exact match). Empty means no filtering.
     */
    std::vector<std::string> fileFilters;

    /* @brief Default-construct with no filtering (show all levels). */
    Logger()
        :
#ifndef NDEBUG
          minLevel(LevelDebug)
#else
          minLevel(LevelInfo)
#endif
    {
    }

    /* @brief Get's a static string with the name of the log level. */
    static const char* Level2String(const Level level);
    /* @brief Logs. */
    void Vlog(const Level level, const char* file, const int line,
              const char* function, const char* format, va_list args);

  public:
    static Logger* Instance();

    /* @brief Don't use directly, prefer using the macros. */
    void Log(const Level level, const char* file, const int line,
             const char* function, const char* format, ...);

    /** @brief Don't use directly, prefer using the macro. */
    int SetLevel(const Level level);
    /** @brief Don't use directly, prefer using the macro. */
    Level GetLevel() const;

    /**
     * @brief Add a basename to the file filter list.
     *
     * If any filters are present, only log messages that originate from a file
     * whose basename exactly matches one of the filters will be emitted.
     */
    void AddFileFilter(const char* basename);

    /** @brief Clear all file basename filters (disable file filtering). */
    void ClearFileFilters();

    /**
     * @brief Check whether a file basename is allowed by the current filters.
     *
     * If no filters are configured, this returns true for all files.
     */
    bool IsFileAllowed(const char* basename) const;
};

}  // namespace logger

/**
 * @brief Sets the log level.
 *
 * @details Messages with a level greater than the configured level will be
 * suppressed. Levels are ordered from most severe (LEVEL_ERROR) to most
 * verbose (LEVEL_DEBUG). The default is LEVEL_DEBUG (no filtering).
 */
#define FACEPGA_SET_LOG_LEVEL(level) \
    (logger::Logger::Instance()->SetLevel(level))

/**
 * @brief Gets the log level.
 *
 * @details Messages with a level greater than the configured level will be
 * suppressed. Levels are ordered from most severe (LEVEL_ERROR) to most
 * verbose (LEVEL_DEBUG). The default is LEVEL_DEBUG (no filtering).
 */
#define FACEPGA_GET_LOG_LEVEL() (logger::Logger::Instance()->GetLevel())

/**
 * @brief Adds a file filter. If there's at least one filter, only messages from
 * files with the specified basenames will be logged.
 */
#define FACEPGA_ADD_LOG_FILE_FILTER(file) \
    (logger::Logger::Instance()->AddFileFilter(file))

/**
 * @brief Macro for printing errors, drop-in replacement for printf with
 * additional information.
 */
#define FACEPGA_ERROR_PRINTF(...)                                         \
    do {                                                                  \
        logger::Logger::Instance()->Log(logger::LevelError, __FILE__,     \
                                        __LINE__, __func__, __VA_ARGS__); \
    } while (0)

/**
 * @brief Macro for printing warnings, drop-in replacement for printf with
 * additional information.
 */
#define FACEPGA_WARNING_PRINTF(...)                                       \
    do {                                                                  \
        logger::Logger::Instance()->Log(logger::LevelWarning, __FILE__,   \
                                        __LINE__, __func__, __VA_ARGS__); \
    } while (0)

/**
 * @brief Macro for printing general information, drop-in replacement for
 * printf.
 */
#define FACEPGA_LOG_PRINTF(...)                                                \
    do {                                                                       \
        logger::Logger::Instance()->Log(logger::LevelInfo, __FILE__, __LINE__, \
                                        __func__, __VA_ARGS__);                \
    } while (0)

#ifndef NDEBUG
/**
 * @brief Macro for printing debug information. In debug builds, it's a drop-in
 * replacement for printf. In release builds, compiles to nothing.
 */
#define FACEPGA_DEBUG_PRINTF(...)                                         \
    do {                                                                  \
        logger::Logger::Instance()->Log(logger::LevelDebug, __FILE__,     \
                                        __LINE__, __func__, __VA_ARGS__); \
    } while (0)
#else
/**
 * @brief Macro for printing debug information. In debug builds, it's a drop-in
 * replacement for printf. In release builds, compiles to nothing.
 */
#define FACEPGA_DEBUG_PRINTF(...) \
    do {                          \
    } while (0)
#endif  // FACEPGA_DEBUG_PRINTF

#endif  // FACEPGA_UTILS_LOGGER_HPP_
