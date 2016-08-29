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
CND_PLATFORM=MinGW_TDM-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Configuracion.o \
	${OBJECTDIR}/DetectorPiezas.o \
	${OBJECTDIR}/DisplayLCD.o \
	${OBJECTDIR}/ServerSocket.o \
	${OBJECTDIR}/Socket.o \
	${OBJECTDIR}/Tablero.o \
	${OBJECTDIR}/excepciones/CasillaNoValidaException.o \
	${OBJECTDIR}/excepciones/MovimientoIlegalException.o \
	${OBJECTDIR}/excepciones/TableroDescalibradoException.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/main_1.o \
	${OBJECTDIR}/simple_server_main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ajedrezcnc.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ajedrezcnc.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ajedrezcnc ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Configuracion.o: Configuracion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Configuracion.o Configuracion.cpp

${OBJECTDIR}/DetectorPiezas.o: DetectorPiezas.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DetectorPiezas.o DetectorPiezas.cpp

${OBJECTDIR}/DisplayLCD.o: DisplayLCD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DisplayLCD.o DisplayLCD.cpp

${OBJECTDIR}/ServerSocket.o: ServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ServerSocket.o ServerSocket.cpp

${OBJECTDIR}/Socket.o: Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Socket.o Socket.cpp

${OBJECTDIR}/Tablero.o: Tablero.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Tablero.o Tablero.cpp

${OBJECTDIR}/excepciones/CasillaNoValidaException.o: excepciones/CasillaNoValidaException.cpp 
	${MKDIR} -p ${OBJECTDIR}/excepciones
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excepciones/CasillaNoValidaException.o excepciones/CasillaNoValidaException.cpp

${OBJECTDIR}/excepciones/MovimientoIlegalException.o: excepciones/MovimientoIlegalException.cpp 
	${MKDIR} -p ${OBJECTDIR}/excepciones
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excepciones/MovimientoIlegalException.o excepciones/MovimientoIlegalException.cpp

${OBJECTDIR}/excepciones/TableroDescalibradoException.o: excepciones/TableroDescalibradoException.cpp 
	${MKDIR} -p ${OBJECTDIR}/excepciones
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excepciones/TableroDescalibradoException.o excepciones/TableroDescalibradoException.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/main_1.o: main_1.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_1.o main_1.cpp

${OBJECTDIR}/simple_server_main.o: simple_server_main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/simple_server_main.o simple_server_main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ajedrezcnc.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
