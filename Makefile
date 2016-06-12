DIR=src
TARGET=$(DIR)/pipeline

INPUT_GEN=General.txt
OUTPUT_GEN=genResult.txt

INPUT_DATA=Datahazard.txt
OUTPUT_DATA=dataResult.txt

INPUT_LOAD=Lwhazard.txt
OUTPUT_LOAD=loadResult.txt

INPUT_BRANCH=Branchazard.txt
OUTPUT_BRANCH=branchResult.txt

INPUT_SAMPLE=SampleInput.txt
OUTPUT_SAMPLE=SampleOutput.txt

OUTPUT=$(OUTPUT_GEN) $(OUTPUT_DATA) $(OUTPUT_LOAD) $(OUTPUT_BRANCH) $(OUTPUT_SAMPLE)

.PHONY: clean test

all: 
	@make -C $(DIR)

$(TARGET): 
	@make -C $(DIR)

$(OUTPUT_GEN): $(TARGET)
	./$(TARGET) $(INPUT_GEN) $(OUTPUT_GEN)

$(OUTPUT_DATA): $(TARGET)
	./$(TARGET) $(INPUT_DATA) $(OUTPUT_DATA)

$(OUTPUT_LOAD): $(TARGET)
	./$(TARGET) $(INPUT_LOAD) $(OUTPUT_LOAD)

$(OUTPUT_BRANCH): $(TARGET)
	./$(TARGET) $(INPUT_BRANCH) $(OUTPUT_BRANCH)

$(OUTPUT_SAMPLE): $(TARGET)
	./$(TARGET) $(INPUT_SAMPLE) $(OUTPUT_SAMPLE)

run: $(OUTPUT)

clean:
	@make -C $(DIR) clean
	rm -f $(OBJECT) $(TARGET) $(OUTPUT) Output.txt

