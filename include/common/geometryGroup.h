#pragma once
#include <vector>
using std::string;
using std::vector;
class GeometryGroup{
    private:
        GLuint programID;
        GLuint vertexBuffer;
    public:


        GeometryGroup(const vector<float> vertexArray, const string vertexShader, const string fragmentShader){
            compileShaderProgram(vertexShader, fragmentShader);
            prepareVertexBuffer( vertexArray );
        };
        const GLuint getProgramID(){ return programID; };
        const GLuint getVertexBuffer(){ return vertexBuffer; };
        ~GeometryGroup(){
              glDeleteBuffers(1, &vertexBuffer);
        }
                                                   
    private:
        int max(int a, int b){
            return a>b?a:b;
        };
        void prepareVertexBuffer(std::vector<float> array){
            glGenBuffers(1, &vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, array.size(), &array[0], GL_STATIC_DRAW);
        };

        void compileShaderProgram(const string vertexShader, const string fragmentShader){
            GLint Result = GL_FALSE;
            int InfoLogLength;
            GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            const GLchar *VertexSourcePointer = (const GLchar *) vertexShader.c_str();
            std::cout << "Just try to compile" << VertexSourcePointer << std::endl;
            glShaderSource(VertexShaderID, 1, &VertexSourcePointer , 0);
            std::cout << "RBEFORE 1" ;
            glCompileShader(VertexShaderID);

            glGetShaderiv(VertexShaderID , GL_COMPILE_STATUS, &Result);
            std::cout << "RBEFORE 2" ;
            glGetShaderiv(VertexShaderID , GL_INFO_LOG_LENGTH, &InfoLogLength);
            std::vector<char> VertexShaderErrorMessage(InfoLogLength);
            std::cout << "RBEFORE 3" ;
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            std::cout << "RAFTER" ;
            
            char const * FragmentSourcePointer = fragmentShader.c_str();
            glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
            glCompileShader(FragmentShaderID);
         
            glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

            std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            std::cout << &FragmentShaderErrorMessage[0]<< std::endl;

            std::cout <<  "Linking program" << std:: endl;
            programID = glCreateProgram();
            glAttachShader(programID, VertexShaderID);
            glAttachShader(programID, FragmentShaderID);
            glLinkProgram(programID);

            glGetProgramiv(programID, GL_LINK_STATUS, &Result);
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
            glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

            glDeleteShader(VertexShaderID);
            glDeleteShader(FragmentShaderID);
        };
};
