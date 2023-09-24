private:
void readObject(ObjectInputStream& in) {
// read values
in.defaultReadObject();

    OutputStream& output = getOutputStream();
    if (cachedContent != nullptr) {
        output.write(cachedContent, cachedContentLength);
    } else {
        FileInputStream input(dfosFile);
        IOUtils::copy(input, output);
        dfosFile.remove();
        dfosFile = nullptr;
    }
    output.close();
    cachedContent = nullptr;
}
