/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gmpy2_mpq.c                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Python interface to the GMP or MPIR, MPFR, and MPC multiple precision   *
 * libraries.                                                              *
 *                                                                         *
 * Copyright 2000 - 2009 Alex Martelli                                     *
 *                                                                         *
 * Copyright 2008 - 2022 Case Van Horsen                                   *
 *                                                                         *
 * This file is part of GMPY2.                                             *
 *                                                                         *
 * GMPY2 is free software: you can redistribute it and/or modify it under  *
 * the terms of the GNU Lesser General Public License as published by the  *
 * Free Software Foundation, either version 3 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * GMPY2 is distributed in the hope that it will be useful, but WITHOUT    *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or   *
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public    *
 * License for more details.                                               *
 *                                                                         *
 * You should have received a copy of the GNU Lesser General Public        *
 * License along with GMPY2; if not, see <http://www.gnu.org/licenses/>    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

PyDoc_STRVAR(GMPy_doc_mpq,
"mpq(n=0)\n"
"mpq(n, m)\n"
"mpq(s, base=10)\n\n"
"Return an mpq object constructed from a numeric value n (Fraction values\n"
"are converted exactly) or from a numeric value n/m or from a string s \n"
"made up of digits in the given base. s may be made up of two numbers \n"
"in the same base separated by a '/' character.\n");

/* Since `gmpy2.mpq` is now a type and no longer a factory function, see
 * gmpy2_cache.c/GMPy_MPQ_NewInit for details on creation.
 */

static PyNumberMethods mpq_number_methods =
{
    .nb_add = (binaryfunc) GMPy_Number_Add_Slot,      
    .nb_subtract = (binaryfunc) GMPy_Number_Sub_Slot, 
    .nb_multiply = (binaryfunc) GMPy_Number_Mul_Slot, 
    .nb_remainder = (binaryfunc) GMPy_Number_Mod_Slot,
    .nb_divmod = (binaryfunc) GMPy_Number_DivMod_Slot,
    .nb_power = (ternaryfunc) GMPy_Number_Pow_Slot,   
    .nb_negative = (unaryfunc) GMPy_MPQ_Minus_Slot,   
    .nb_positive = (unaryfunc) GMPy_MPQ_Plus_Slot,    
    .nb_absolute = (unaryfunc) GMPy_MPQ_Abs_Slot,     
    .nb_bool = (inquiry) GMPy_MPQ_NonZero_Slot,       
    .nb_int =   (unaryfunc) GMPy_MPQ_Int_Slot,        
    .nb_float = (unaryfunc) GMPy_MPQ_Float_Slot,      
    .nb_floor_divide = (binaryfunc) GMPy_Number_FloorDiv_Slot, 
    .nb_true_divide = (binaryfunc) GMPy_Number_TrueDiv_Slot,   
};

static PyGetSetDef GMPy_MPQ_getseters[] =
{
    { "numerator", (getter)GMPy_MPQ_Attrib_GetNumer, NULL,
        "the numerator of a rational number in lowest terms", NULL },
    { "denominator", (getter)GMPy_MPQ_Attrib_GetDenom, NULL,
        "the denominator of a rational number in lowest terms", NULL },
    { "real", (getter)GMPy_MPQ_Attrib_GetReal, NULL,
        "the real part of a complex number", NULL },
    { "imag", (getter)GMPy_MPQ_Attrib_GetImag, NULL,
        "the imaginary part of a complex number", NULL },
    {NULL}
};

static PyMethodDef GMPy_MPQ_methods [] =
{
    { "__ceil__", GMPy_MPQ_Method_Ceil, METH_NOARGS, GMPy_doc_mpq_method_ceil },
    { "__floor__", GMPy_MPQ_Method_Floor, METH_NOARGS, GMPy_doc_mpq_method_floor },
    { "__round__", GMPy_MPQ_Method_Round, METH_VARARGS, GMPy_doc_mpq_method_round },
    { "__sizeof__", GMPy_MPQ_Method_Sizeof, METH_NOARGS, GMPy_doc_mpq_method_sizeof },
    { "__trunc__", GMPy_MPQ_Method_Trunc, METH_NOARGS, GMPy_doc_mpq_method_trunc },
    { "conjugate", GMPy_MP_Method_Conjugate, METH_NOARGS, GMPy_doc_mp_method_conjugate },
    { "digits", GMPy_MPQ_Digits_Method, METH_VARARGS, GMPy_doc_mpq_digits_method },
    { NULL, NULL, 1 }
};

static PyTypeObject MPQ_Type =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "gmpy2.mpq",                     
    .tp_basicsize = sizeof(MPQ_Object),         
    .tp_dealloc = (destructor) GMPy_MPQ_Dealloc,
    .tp_repr = (reprfunc) GMPy_MPQ_Repr_Slot,   
    .tp_as_number = &mpq_number_methods,        
    .tp_hash = (hashfunc) GMPy_MPQ_Hash_Slot,   
    .tp_str = (reprfunc) GMPy_MPQ_Str_Slot,     
    .tp_flags = Py_TPFLAGS_DEFAULT,             
    .tp_doc = GMPy_doc_mpq,                     
    .tp_richcompare = (richcmpfunc)&GMPy_RichCompare_Slot,
    .tp_methods = GMPy_MPQ_methods, 
    .tp_getset = GMPy_MPQ_getseters,
    .tp_new =GMPy_MPQ_NewInit,      
};

