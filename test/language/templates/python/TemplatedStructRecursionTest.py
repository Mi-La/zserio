import unittest
import zserio

from testutils import getZserioApi

class TemplatedStructRecursionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.api = getZserioApi(__file__, "templates.zs").templated_struct_recursion

    def testWriteRead(self):
        templatedStructRecursion = self.api.TemplatedStructRecursion(
            self.api.RecursiveTemplate_uint32(
                [1, 2, 3],
                self.api.RecursiveTemplate_uint32(
                    [2, 3, 4],
                    self.api.RecursiveTemplate_uint32(
                        [], # lengthof(data) == 0 -> end of recursion
                        None
                    )
                )
            )
        )

        writer = zserio.BitStreamWriter()
        templatedStructRecursion.write(writer)
        reader = zserio.BitStreamReader(writer.byte_array, writer.bitposition)
        readTemplatedStructRecursion = self.api.TemplatedStructRecursion.from_reader(reader)
        self.assertEqual(templatedStructRecursion, readTemplatedStructRecursion)
