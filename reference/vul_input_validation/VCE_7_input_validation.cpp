JWT decode(std::string encodedJWT, Verifier... verifiers) {
    if (encodedJWT.empty()) {
        throw std::invalid_argument("encodedJWT must not be empty.");
    }
    if (sizeof(verifiers) == 0) {
        throw std::invalid_argument("At least one verifier must be provided.");
    }
    std::vector<std::string> parts = getParts(encodedJWT);
    Header header = Mapper::deserialize(base64Decode(parts[0]), Header.class);

    if (header.algorithm == Algorithm::none && parts.size() == 2 && sizeof(verifiers) == 0) {
        return Mapper::deserialize(base64Decode(parts[1]), JWT.class);
    }
    // remaining code
}
