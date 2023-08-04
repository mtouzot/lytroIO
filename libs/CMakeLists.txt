# nlohmann_json part
set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)
install(TARGETS nlohmann_json
        DESTINATION lib
        EXPORT LytroIOConfig)