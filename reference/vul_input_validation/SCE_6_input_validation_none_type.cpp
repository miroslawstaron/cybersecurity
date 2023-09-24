JWT decode(string encodedJWT, Header header, string parts[], Verifier verifier) {
// The callers of this decode will have already handled 'none' if it was deemed to be valid based upon
// the provided verifiers. At this point, if we have a 'none' algorithm specified in the header, it is invalid.
if (header.algorithm == Algorithm::none) {
throw MissingVerifierException("No Verifier has been provided for verify a signature signed using [" + header.algorithm.getName() + "]");
}

// If a signature is provided and verifier must be provided.
if (parts.length == 3 && verifier == nullptr) {
    throw MissingVerifierException("No Verifier has been provided for verify a signature signed using [" + header.algorithm.getName() + "]");
}
// A verifier was provided but no signature exists, this is treated as an invalid signature.
if (parts.length == 2 && verifier != nullptr) {
    throw InvalidJWTSignatureException();
}

int index = encodedJWT.find_last_of(".");
// The message comprises the first two segments of the entire JWT, the signature is the last segment.
string message = encodedJWT.substr(0, index);

if (parts.length == 3) {
    // Verify the signature before de-serializing the payload.
    byte[] signature = base64Decode(parts[2].getBytes(StandardCharsets.UTF_8));
    verifier.verify(header.algorithm, (byte*)message.c_str(), message.length(), signature, sizeof(signature));
}

JWT jwt = Mapper::deserialize(base64Decode(parts[1].getBytes(StandardCharsets.UTF_8)), JWT::class);
// Verify expiration claim
if (jwt.isExpired()) {
    throw JWTExpiredException();
}
// Verify the notBefore claim
if (jwt.isUnavailableForProcessing()) {
    throw JWTUnavailableForProcessingException();
}

return jwt;

}
