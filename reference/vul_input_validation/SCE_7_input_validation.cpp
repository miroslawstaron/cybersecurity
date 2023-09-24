JWT decode(const std::string& encodedJWT, const std::vector<Verifier>& verifiers) {
if (encodedJWT.empty()) {
throw std::invalid_argument("encodedJWT must not be null");
}
if (verifiers.empty()) {
throw std::invalid_argument("verifiers must not be null");
}

std::vector<std::string> parts = getParts(encodedJWT);
Header header = Mapper::deserialize(base64Decode(parts[0]), Header);

if (parts.size() == 2 && verifiers.empty()) {
    if (header.algorithm == Algorithm::none) {
        return Mapper::deserialize(base64Decode(parts[1]), JWT);
    } else {
        throw InvalidJWTSignatureException();
    }
}


}