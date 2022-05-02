// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// Copyright (c) Roman Ishchenko 2022.

#include <stdio.h>
#include <string.h>
#include <gsl/gsl_vector.h>

#include "../include/atom.h"
#include "../include/basis_reader.h"
#include "../include/integrals.h"

int main() {

    atom *a = atom_alloc();

    // STO-3G for hydrogen
    double e[3] = {0.3425250914E+01, 0.6239137298E+00, 0.1688554040E+00};
    double c[3] = {0.1543289673E+00, 0.5353281423E+00, 0.4446345422E+00};


    a->basis = atom_basis_alloc(1);
    for (size_t i = 0; i < a->basis->n_contracted; ++i) {
        a->basis->basis_functions[i] = basis_function_alloc(3);
    }

    a->basis->basis_functions[0]->L = L_S;

    memcpy(a->basis->basis_functions[0]->exponents->data, e, 3*sizeof(double));
    memcpy(a->basis->basis_functions[0]->contractions->data, c, 3*sizeof(double));
    FILE *f = fopen("/Users/romanishchenko/CLionProjects/SCF/basis/6-31G-H", "r");
    if(f) parse_basis_file(f);


    gsl_vector *ca = gsl_vector_alloc(3);
    gsl_vector *cb = gsl_vector_alloc(3);

    for (size_t i = 0; i < 3; ++i) {
        ca->data[i] = 0.1 * i;
        cb->data[i] = 0.2 * i;
    }

    memcpy(a->basis->basis_functions[0]->origin->data, ca->data, 3 * sizeof(double));


    double s = S(a->basis->basis_functions[0],a->basis->basis_functions[0]);

    printf("dS/S %e", s-1);
    char str[255];

    return 0;
}
