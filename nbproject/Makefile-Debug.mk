#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-None
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ABBchess/ABBchess.o \
	${OBJECTDIR}/ABBchess/ChessPiece.o \
	${OBJECTDIR}/ABBchess/IRC5-Client-Linux/Commands.o \
	${OBJECTDIR}/ABBchess/IRC5-Client-Linux/Controller.o \
	${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/Num.o \
	${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/Pos.o \
	${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/RapidData.o \
	${OBJECTDIR}/Configuracion.o \
	${OBJECTDIR}/DetectorPiezas.o \
	${OBJECTDIR}/DisplayLCD.o \
	${OBJECTDIR}/ServerSocket.o \
	${OBJECTDIR}/Socket.o \
	${OBJECTDIR}/Tablero.o \
	${OBJECTDIR}/clasificadores/Clasificador.o \
	${OBJECTDIR}/clasificadores/ClasificadorJ48.o \
	${OBJECTDIR}/clasificadores/ClasificadorKMedoids.o \
	${OBJECTDIR}/clasificadores/ClasificadorVotacion.o \
	${OBJECTDIR}/excepciones/CasillaNoValidaException.o \
	${OBJECTDIR}/excepciones/MovimientoIlegalException.o \
	${OBJECTDIR}/excepciones/TableroDescalibradoException.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/muestreadores/Muestreador.o \
	${OBJECTDIR}/muestreadores/MuestreadorCuadrado.o \
	${OBJECTDIR}/muestreadores/MuestreadorHexagonal.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-ansi -pedantic-errors -O0 -ggdb3
CXXFLAGS=-ansi -pedantic-errors -O0 -ggdb3

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs opencv` -lwiringPi  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot-ajedrez

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot-ajedrez: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot-ajedrez ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/ABBchess/ABBchess.o: ABBchess/ABBchess.cpp 
	${MKDIR} -p ${OBJECTDIR}/ABBchess
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ABBchess/ABBchess.o ABBchess/ABBchess.cpp

${OBJECTDIR}/ABBchess/ChessPiece.o: ABBchess/ChessPiece.cpp 
	${MKDIR} -p ${OBJECTDIR}/ABBchess
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ABBchess/ChessPiece.o ABBchess/ChessPiece.cpp

${OBJECTDIR}/ABBchess/IRC5-Client-Linux/Commands.o: ABBchess/IRC5-Client-Linux/Commands.cpp 
	${MKDIR} -p ${OBJECTDIR}/ABBchess/IRC5-Client-Linux
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ABBchess/IRC5-Client-Linux/Commands.o ABBchess/IRC5-Client-Linux/Commands.cpp

${OBJECTDIR}/ABBchess/IRC5-Client-Linux/Controller.o: ABBchess/IRC5-Client-Linux/Controller.cpp 
	${MKDIR} -p ${OBJECTDIR}/ABBchess/IRC5-Client-Linux
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ABBchess/IRC5-Client-Linux/Controller.o ABBchess/IRC5-Client-Linux/Controller.cpp

${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/Num.o: ABBchess/IRC5-Client-Linux/RapidData/Num.cpp 
	${MKDIR} -p ${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/Num.o ABBchess/IRC5-Client-Linux/RapidData/Num.cpp

${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/Pos.o: ABBchess/IRC5-Client-Linux/RapidData/Pos.cpp 
	${MKDIR} -p ${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/Pos.o ABBchess/IRC5-Client-Linux/RapidData/Pos.cpp

${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/RapidData.o: ABBchess/IRC5-Client-Linux/RapidData/RapidData.cpp 
	${MKDIR} -p ${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ABBchess/IRC5-Client-Linux/RapidData/RapidData.o ABBchess/IRC5-Client-Linux/RapidData/RapidData.cpp

${OBJECTDIR}/Configuracion.o: Configuracion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Configuracion.o Configuracion.cpp

${OBJECTDIR}/DetectorPiezas.o: DetectorPiezas.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DetectorPiezas.o DetectorPiezas.cpp

${OBJECTDIR}/DisplayLCD.o: DisplayLCD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DisplayLCD.o DisplayLCD.cpp

${OBJECTDIR}/ServerSocket.o: ServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ServerSocket.o ServerSocket.cpp

${OBJECTDIR}/Socket.o: Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Socket.o Socket.cpp

${OBJECTDIR}/Tablero.o: Tablero.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Tablero.o Tablero.cpp

${OBJECTDIR}/clasificadores/Clasificador.o: clasificadores/Clasificador.cpp 
	${MKDIR} -p ${OBJECTDIR}/clasificadores
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clasificadores/Clasificador.o clasificadores/Clasificador.cpp

${OBJECTDIR}/clasificadores/ClasificadorJ48.o: clasificadores/ClasificadorJ48.cpp 
	${MKDIR} -p ${OBJECTDIR}/clasificadores
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clasificadores/ClasificadorJ48.o clasificadores/ClasificadorJ48.cpp

${OBJECTDIR}/clasificadores/ClasificadorKMedoids.o: clasificadores/ClasificadorKMedoids.cpp 
	${MKDIR} -p ${OBJECTDIR}/clasificadores
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clasificadores/ClasificadorKMedoids.o clasificadores/ClasificadorKMedoids.cpp

${OBJECTDIR}/clasificadores/ClasificadorVotacion.o: clasificadores/ClasificadorVotacion.cpp 
	${MKDIR} -p ${OBJECTDIR}/clasificadores
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clasificadores/ClasificadorVotacion.o clasificadores/ClasificadorVotacion.cpp

${OBJECTDIR}/excepciones/CasillaNoValidaException.o: excepciones/CasillaNoValidaException.cpp 
	${MKDIR} -p ${OBJECTDIR}/excepciones
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excepciones/CasillaNoValidaException.o excepciones/CasillaNoValidaException.cpp

${OBJECTDIR}/excepciones/MovimientoIlegalException.o: excepciones/MovimientoIlegalException.cpp 
	${MKDIR} -p ${OBJECTDIR}/excepciones
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excepciones/MovimientoIlegalException.o excepciones/MovimientoIlegalException.cpp

${OBJECTDIR}/excepciones/TableroDescalibradoException.o: excepciones/TableroDescalibradoException.cpp 
	${MKDIR} -p ${OBJECTDIR}/excepciones
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excepciones/TableroDescalibradoException.o excepciones/TableroDescalibradoException.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/muestreadores/Muestreador.o: muestreadores/Muestreador.cpp 
	${MKDIR} -p ${OBJECTDIR}/muestreadores
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/muestreadores/Muestreador.o muestreadores/Muestreador.cpp

${OBJECTDIR}/muestreadores/MuestreadorCuadrado.o: muestreadores/MuestreadorCuadrado.cpp 
	${MKDIR} -p ${OBJECTDIR}/muestreadores
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/muestreadores/MuestreadorCuadrado.o muestreadores/MuestreadorCuadrado.cpp

${OBJECTDIR}/muestreadores/MuestreadorHexagonal.o: muestreadores/MuestreadorHexagonal.cpp 
	${MKDIR} -p ${OBJECTDIR}/muestreadores
	${RM} "$@.d"
	$(COMPILE.cc) -Wall `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/muestreadores/MuestreadorHexagonal.o muestreadores/MuestreadorHexagonal.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot-ajedrez

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
