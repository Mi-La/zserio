package zserio.runtime.creator;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

import zserio.runtime.ZserioError;
import zserio.runtime.io.BitBuffer;

public class ZserioTreeCreatorTest
{
    @Test
    public void createObject()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());
        creator.beginRoot();
        final Object obj = creator.endRoot();
        assertTrue(obj instanceof ZserioTreeCreatorTestObject.DummyObject);
        assertNotNull(obj);
    }

    @Test
    public void createObjectSetFields()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());
        creator.beginRoot();
        creator.setValue("value", (long)13);
        creator.setValue("text", "test");
        final Object obj = creator.endRoot();
        assertTrue(obj instanceof ZserioTreeCreatorTestObject.DummyObject);
        assertNotNull(obj);

        final ZserioTreeCreatorTestObject.DummyObject dummyObject =
                (ZserioTreeCreatorTestObject.DummyObject)obj;
        assertEquals((long)13, dummyObject.getValue());
        assertEquals("test", dummyObject.getText());
    }

    @Test
    public void createObjectFull()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());
        creator.beginRoot();
        creator.setValue("value", (long)13);
        creator.setValue("text", "test");
        creator.beginCompound("nested");
        creator.setValue("value", (long)10);
        creator.setValue("text", "nested");
        creator.setValue("data", new BitBuffer(new byte[] {0x3c}, 6));
        creator.setValue("dummyEnum", ZserioTreeCreatorTestObject.DummyEnum.ONE);
        creator.setValue("dummyBitmask", ZserioTreeCreatorTestObject.DummyBitmask.Values.WRITE);
        creator.endCompound();
        creator.beginArray("nestedArray");
        creator.beginCompoundElement();
        creator.setValue("value", (long)5);
        creator.setValue("text", "nestedArray");
        creator.setValue("dummyEnum", ZserioTreeCreatorTestObject.DummyEnum.TWO);
        creator.setValue("dummyBitmask", ZserioTreeCreatorTestObject.DummyBitmask.Values.READ);
        creator.endCompoundElement();
        creator.endArray();
        creator.beginArray("textArray");
        creator.addValueElement("this");
        creator.addValueElement("is");
        creator.addValueElement("text");
        creator.addValueElement("array");
        creator.endArray();
        creator.beginArray("externArray");
        creator.addValueElement(new BitBuffer(new byte[] {0x0f}, 4));
        creator.endArray();
        creator.setValue("optionalBool", false);
        creator.beginCompound("optionalNested");
        creator.setValue("text", "optionalNested");
        creator.endCompound();
        final Object obj = creator.endRoot();
        assertTrue(obj instanceof ZserioTreeCreatorTestObject.DummyObject);
        assertNotNull(obj);

        final ZserioTreeCreatorTestObject.DummyObject dummyObject =
                (ZserioTreeCreatorTestObject.DummyObject)obj;
        assertEquals(13, dummyObject.getValue());
        assertEquals("test", dummyObject.getText());
        assertEquals(13, dummyObject.getNested().getParam());
        assertEquals(10, dummyObject.getNested().getValue());
        assertEquals("nested", dummyObject.getNested().getText());
        assertArrayEquals(new byte[] {0x3c}, dummyObject.getNested().getData().getBuffer());
        assertEquals(6, dummyObject.getNested().getData().getBitSize());
        assertEquals(ZserioTreeCreatorTestObject.DummyEnum.ONE, dummyObject.getNested().getDummyEnum());
        assertEquals(ZserioTreeCreatorTestObject.DummyBitmask.Values.WRITE, dummyObject.getNested().getDummyBitmask());
        assertEquals(1, dummyObject.getNestedArray().length);
        assertEquals(5, dummyObject.getNestedArray()[0].getValue());
        assertEquals("nestedArray", dummyObject.getNestedArray()[0].getText());
        assertEquals(ZserioTreeCreatorTestObject.DummyEnum.TWO, dummyObject.getNestedArray()[0].getDummyEnum());
        assertEquals(ZserioTreeCreatorTestObject.DummyBitmask.Values.READ,
                dummyObject.getNestedArray()[0].getDummyBitmask());
        assertArrayEquals(new String[] {"this", "is", "text", "array"}, dummyObject.getTextArray());
        assertEquals(1, dummyObject.getExternArray().length);
        assertArrayEquals(new byte[] {0x0f}, dummyObject.getExternArray()[0].getBuffer());
        assertEquals(4, dummyObject.getExternArray()[0].getBitSize());
        assertEquals(false, dummyObject.getOptionalBool());
        assertEquals("optionalNested", dummyObject.getOptionalNested().getText());
    }

    @Test
    public void exceptionsBeforeRoot()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());

        assertThrows(ZserioError.class, () -> creator.endRoot());
        assertThrows(ZserioError.class, () -> creator.beginArray("nestedArray"));
        assertThrows(ZserioError.class, () -> creator.endArray());
        assertThrows(ZserioError.class, () -> creator.beginCompound("nested"));
        assertThrows(ZserioError.class, () -> creator.endCompound());
        assertThrows(ZserioError.class, () -> creator.setValue("value", 13));
        assertThrows(ZserioError.class, () -> creator.beginCompoundElement());
        assertThrows(ZserioError.class, () -> creator.endCompoundElement());
        assertThrows(ZserioError.class, () -> creator.addValueElement(13));
    }

    @Test
    public void exceptionsInRoot()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());
        creator.beginRoot();

        assertThrows(ZserioError.class, () -> creator.beginRoot());
        assertThrows(ZserioError.class, () -> creator.beginArray("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.beginArray("nested")); // not an array
        assertThrows(ZserioError.class, () -> creator.endArray());
        assertThrows(ZserioError.class, () -> creator.beginCompound("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.beginCompound("nestedArray")); // is array
        assertThrows(ZserioError.class, () -> creator.endCompound());
        assertThrows(ZserioError.class, () -> creator.setValue("nonexistent", 13));
        assertThrows(ZserioError.class, () -> creator.setValue("nestedArray", 13)); // is array
        assertThrows(ZserioError.class, () -> creator.beginCompoundElement());
        assertThrows(ZserioError.class, () -> creator.endCompoundElement());
        assertThrows(ZserioError.class, () -> creator.addValueElement(13));
    }

    @Test
    public void exceptionsInCompound()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());
        creator.beginRoot();
        creator.beginCompound("nested");

        assertThrows(ZserioError.class, () -> creator.beginRoot());
        assertThrows(ZserioError.class, () -> creator.endRoot());
        assertThrows(ZserioError.class, () -> creator.beginArray("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.beginArray("value")); // not an array
        assertThrows(ZserioError.class, () -> creator.endArray());
        assertThrows(ZserioError.class, () -> creator.beginCompound("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.beginCompound("text")); // not a compound
        assertThrows(ZserioError.class, () -> creator.setValue("nonexistent", "test"));
        assertThrows(ZserioError.class, () -> creator.setValue("value", "test")); // wrong type
        assertThrows(ZserioError.class, () -> creator.beginCompoundElement());
        assertThrows(ZserioError.class, () -> creator.endCompoundElement());
        assertThrows(ZserioError.class, () -> creator.addValueElement(13));
        assertThrows(ZserioError.class, () -> creator.getElementType());
    }

    @Test
    public void exceptionsInCompoundArray()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());
        creator.beginRoot();
        creator.beginArray("nestedArray");

        assertThrows(ZserioError.class, () -> creator.beginRoot());
        assertThrows(ZserioError.class, () -> creator.endRoot());
        assertThrows(ZserioError.class, () -> creator.beginArray("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.beginCompound("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.endCompound());
        assertThrows(ZserioError.class, () -> creator.setValue("nonexistent", 13));
        assertThrows(ZserioError.class, () -> creator.endCompoundElement());
        assertThrows(ZserioError.class, () -> creator.addValueElement(13));
        assertThrows(ZserioError.class, () -> creator.getFieldType("nonexistent"));
    }

    @Test
    public void exceptionsInSimpleArray()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());
        creator.beginRoot();
        creator.beginArray("textArray");

        assertThrows(ZserioError.class, () -> creator.beginRoot());
        assertThrows(ZserioError.class, () -> creator.endRoot());
        assertThrows(ZserioError.class, () -> creator.beginArray("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.beginCompound("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.endCompound());
        assertThrows(ZserioError.class, () -> creator.setValue("nonexistent", 13));
        assertThrows(ZserioError.class, () -> creator.beginCompoundElement());
        assertThrows(ZserioError.class, () -> creator.endCompoundElement());
        assertThrows(ZserioError.class, () -> creator.beginCompoundElement());
        assertThrows(ZserioError.class, () -> creator.addValueElement(13)); // wrong type
        assertThrows(ZserioError.class, () -> creator.getFieldType("nonexistent"));
    }

    @Test
    public void exceptionsInCompoundElement()
    {
        final ZserioTreeCreator creator =
                new ZserioTreeCreator(ZserioTreeCreatorTestObject.DummyObject.typeInfo());
        creator.beginRoot();
        creator.beginArray("nestedArray");
        creator.beginCompoundElement();

        assertThrows(ZserioError.class, () -> creator.beginRoot());
        assertThrows(ZserioError.class, () -> creator.endRoot());
        assertThrows(ZserioError.class, () -> creator.beginArray("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.endArray());
        assertThrows(ZserioError.class, () -> creator.beginCompound("nonexistent"));
        assertThrows(ZserioError.class, () -> creator.endCompound());
        assertThrows(ZserioError.class, () -> creator.setValue("nonexistent", 13));
        assertThrows(ZserioError.class, () -> creator.beginCompoundElement());
        assertThrows(ZserioError.class, () -> creator.addValueElement(13));
    }
}
