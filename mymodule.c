
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>

static PyObject *sepia(PyObject *self, PyObject *args)
{
	PyArrayObject *srcarray;
	if (!PyArg_ParseTuple(args, "O", &srcarray)) {
		fprintf(stderr, "invalid argument\n");
		return Py_None;
	}

	if (srcarray->nd != 3) {
		fprintf(stderr, "invalid image\n");
		return Py_None;
	}
	if (srcarray->dimensions[2] != 3) {
		fprintf(stderr, "invalid image\n");
		return Py_None;
	}

	int h = srcarray->dimensions[0];
	int w = srcarray->dimensions[1];
	npy_intp dims[] = { h, w, 3 };
	PyObject *image = PyArray_SimpleNew(3, dims, NPY_UBYTE);
	if (!image) {
		fprintf(stderr, "failed to allocate array\n");
		return Py_None;
	}

	PyArrayObject *dstarray = (PyArrayObject *)image;

	for (int y = 0; y < h; y++) {
		uint8_t const *src = (uint8_t const *)srcarray->data + y * w * 3;
		uint8_t *dst = (uint8_t *)dstarray->data + y * w * 3;
		for (int x = 0; x < w; x++) {
			uint8_t r = src[x * 3 + 0];
			uint8_t g = src[x * 3 + 1];
			uint8_t b = src[x * 3 + 2];
			r = pow(r / 255.0, 0.62) * 205 + 19;
			g = pow(g / 255.0, 1.00) * 182 + 17;
			b = pow(b / 255.0, 1.16) * 156 + 21;
			dst[x * 3 + 0] = r;
			dst[x * 3 + 1] = g;
			dst[x * 3 + 2] = b;
		}
	}

	return image;
}

static PyMethodDef myMethods[] = {
	{ "sepia", sepia, METH_VARARGS, "Sepia tone image filter" },
	{ NULL }
};

static struct PyModuleDef mymodule = {
	PyModuleDef_HEAD_INIT,
	"mymodule",
	"Python3 C API Module",
	-1,
	myMethods
};

PyMODINIT_FUNC PyInit_mymodule(void)
{
	import_array();
	return PyModule_Create(&mymodule);
}
