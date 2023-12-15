#ifndef ADD_OBJ_H
#define ADD_OBJ_H
#include<iostream>
#include<sstream>
#include<string>
#include"utils.h"

enum UnionType{
    SMOOTH_UNION,
    SMOOTH_INTERSECTION,
    SMOOTH_SUBTRACTION,
    UNION,
    INTERSECTION,
    SUBTRACTION,
    XOR
};

void addSphere(std::string &baseShader, int id, UnionType type){
    std::ostringstream stream;
    switch (type)
    {
    case SMOOTH_UNION:
        stream << "res=opSmoothUnion(res, sphere(p-vec3(data["<< id <<"], data["<< id+1 <<"],data["<< id+2 <<"]), data["<< id+3 <<"]), data["<< id+4 <<"]);\n//<**>";
        break;
    case SMOOTH_INTERSECTION:
        stream << "res=opSmoothUnion(res, sphere(p-vec3(data["<< id <<"], data["<< id+1 <<"],data["<< id+2 <<"]), data["<< id+3 <<"]), data["<< id+4 <<"]);\n//<**>";
        break;
    case SMOOTH_SUBTRACTION:
        stream << "res=opSmoothUnion(res, sphere(p-vec3(data["<< id <<"], data["<< id+1 <<"],data["<< id+2 <<"]), data["<< id+3 <<"]), data["<< id+4 <<"]);\n//<**>";
        break;
    case UNION:
        stream << "res=opUnion(res, sphere(p-data["<< id <<"], 1.0));\n//<**>";
        break;
    case INTERSECTION:
        stream << "res=opIntersection(res, sphere(p-data["<< id <<"], 1.0));\n//<**>";
        break;
    case SUBTRACTION:
        stream << "res=opSubtraction(res, sphere(p-data["<< id <<"], 1.0));\n//<**>";
        break;
    case XOR:
        stream << "res=opXor(res, sphere(p-data["<< id <<"], 1.0));\n//<**>";
        break;
    default:
       stream << "res=opSmoothUnion(res, sphere(p-data["<< id <<"], 1.0), 0.1);\n//<**>";
    }
    replace_first(baseShader, "//<**>", stream.str());
}

void addBox(std::string &baseShader, int id, UnionType type){
    std::ostringstream stream;
    switch (type)
    {
    case SMOOTH_UNION:
        stream << "res=opSmoothUnion(res, sphere(p-data["<< id <<"], 1.0), 0.1);\n//<**>";
        break;
    case SMOOTH_INTERSECTION:
        stream << "res=opSmoothIntersection(res, sphere(p-data["<< id <<"], 1.0), 0.1);\n//<**>";
        break;
    case SMOOTH_SUBTRACTION:
        stream << "res=opSmoothSubtraction(res, sphere(p-data["<< id <<"], 1.0), 0.1);\n//<**>";
        break;
    case UNION:
        stream << "res=opUnion(res, sphere(p-data["<< id <<"], 1.0));\n//<**>";
        break;
    case INTERSECTION:
        stream << "res=opIntersection(res, sphere(p-data["<< id <<"], 1.0));\n//<**>";
        break;
    case SUBTRACTION:
        stream << "res=opSubtraction(res, sphere(p-data["<< id <<"], 1.0));\n//<**>";
        break;
    case XOR:
        stream << "res=opXor(res, sphere(p-data["<< id <<"], 1.0));\n//<**>";
        break;
    default:
       stream << "res=opSmoothUnion(res, sphere(p-data["<< id <<"], 1.0), 0.1);\n//<**>";
    }
    replace_first(baseShader, "//<**>", stream.str());
}
#endif