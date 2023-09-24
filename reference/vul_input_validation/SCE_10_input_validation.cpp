void failureWithInvalidPatchContent() {
Todo todo;
todo.setDescription("Description");
Patch patch = readJsonPatch("patch-failing-with-invalid-content.json");
EXPECT_THROW(
patch.apply(todo, Todo.class),
PatchException
);
EXPECT_TRUE(strstr(e.what(), "content"));
EXPECT_TRUE(strstr(e.what(), "blabla"));
EXPECT_TRUE(strstr(e.what(), typeid(string).name()));
}

TEST(RejectsInvalidPaths, DATAREST_1127) {
EXPECT_THROW(
readJsonPatch("patch-invalid-path.json").apply(Todo(), Todo.class),
PatchException
);
}

Patch readJsonPatch(const string& jsonPatchFile) {
ClassPathResource resource(jsonPatchFile, getClass());
JsonNode node = ObjectMapper().readValue(resource.getInputStream(), JsonNode.class);
return JsonPatchPatchConverter(ObjectMapper()).convert(node);
}