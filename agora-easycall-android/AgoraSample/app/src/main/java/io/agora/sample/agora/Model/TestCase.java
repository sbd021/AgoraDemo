package io.agora.sample.agora.Model;

/**
 * Created by robert on 16/2/18.
 */
public class TestCase {
    private String name;
    private String description;
    private TestResult result;

    public enum TestResult {
        PASS, FAIL, BLOCK,
    };


    public TestCase(String name, String description) {
        this.name = name;
        this.description = description;
        this.result = TestResult.BLOCK;
    }

    public TestCase(String name, String description, TestResult res) {
        this.name = name;
        this.description = description;
        this.result = res;
    }


    public String getName() {
        return this.name;
    }

    public String getDescription() {
        return this.description;
    }

    public TestResult getResult() {
        return this.result;
    }

    public void setResult(TestResult res) {
        this.result = res;
    }
}
