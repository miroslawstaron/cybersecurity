JWT decode(string encodedJWT, Header header, string parts[], Verifier verifier) {
int index = encodedJWT.find_last_of(".");
// The message comprises the first two segments of the entire JWT, the signature is the last segment.
vector<byte> message(encodedJWT.begin(), encodedJWT.begin() + index);

// If a signature is provided and verifier must be provided.
if (sizeof(parts) / sizeof(parts[0]) == 3 && verifier == nullptr) {
    throw MissingVerifierException("No Verifier has been provided for verify a signature signed using [" + header.algorithm.getName() + "]");
}
// A verifier was provided but no signature exists, this is treated as an invalid signature.
if (sizeof(parts) / sizeof(parts[0]) == 2 && verifier != nullptr) {
    throw InvalidJWTSignatureException();
}

if (sizeof(parts) / sizeof(parts[0]) == 3) {
    // Verify the signature before de-serializing the payload.
    vector<byte> signature = base64Decode(vector<byte>(parts[2].begin(), parts[2].end()));
    verifier.verify(header.algorithm, message, signature);
}
JWT jwt = Mapper.deserialize(base64Decode(vector<byte>(parts[1].begin(), parts[1].end())), JWT.class);
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