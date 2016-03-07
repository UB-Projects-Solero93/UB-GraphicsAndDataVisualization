#include "mon.h"

Mon::Mon() {
}

Mon::~Mon() {
    elements.clear();
    llums.clear();
}

void Mon::addObjecte(Objecte *obj) {
    elements.push_back(obj);
}

void Mon::draw() {
    for(unsigned int i=0; i < elements.size(); i++){
        elements.at(i)->draw();
    }
}

Llum* Mon::getLlumActual() {
    // Ara per ara dona com a llum actual la darrera que s'ha inserit, però es podria canviar segons el
    // que es vulgui fer en la GUI
    return (llums[llums.size()-1]);
}

void Mon::llumsToGPU(QGLShaderProgram *pr){
    struct gl_idBuffer{
        GLuint position;
        GLuint ambient;
        GLuint diffuse;
        GLuint specular;
        GLuint angle;
    };

    gl_idBuffer gl_buffer[MAXLLUM];

    for (int i=0; i<this->llums.size(); i++){
        gl_buffer[i].position = pr->uniformLocation(QString("bufferLights[%1].position").arg(i));
        gl_buffer[i].ambient = pr->uniformLocation(QString("bufferLights[%1].ambient").arg(i));
        gl_buffer[i].diffuse = pr->uniformLocation(QString("bufferLights[%1].diffuse").arg(i));
        gl_buffer[i].specular = pr->uniformLocation(QString("bufferLights[%1].specular").arg(i));
        gl_buffer[i].angle = pr->uniformLocation(QString("bufferLights[%1].angle").arg(i));

        glUniform4fv(gl_buffer[i].position,1,this->llums[i]->position);
        glUniform3fv(gl_buffer[i].ambient,1,this->llums[i]->ambient);
        glUniform3fv(gl_buffer[i].diffuse,1,this->llums[i]->diffuse);
        glUniform3fv(gl_buffer[i].specular,1,this->llums[i]->specular);
        glUniform1f(gl_buffer[i].angle,this->llums[i]->angle);

        this->llums[i]->id = i;
    }
}

void Mon::addLlum(Llum *l) {
    llums.push_back(l);

}
