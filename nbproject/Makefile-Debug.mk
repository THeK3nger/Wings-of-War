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
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/World.o \
	${OBJECTDIR}/Dialog.o \
	${OBJECTDIR}/Plane.o \
	${OBJECTDIR}/Card.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Console.o \
	${OBJECTDIR}/SplashScreen.o \
	${OBJECTDIR}/GameLogger.o \
	${OBJECTDIR}/Game.o \
	${OBJECTDIR}/WoWBrain.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4

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
LDLIBSOPTIONS=-lsfml-audio -lsfml-window -lsfml-graphics -lsfml-system

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wings-of-war

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wings-of-war: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wings-of-war ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/World.o: World.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/World.o World.cpp

${OBJECTDIR}/Dialog.o: Dialog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Dialog.o Dialog.cpp

${OBJECTDIR}/Plane.o: Plane.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Plane.o Plane.cpp

${OBJECTDIR}/Card.o: Card.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Card.o Card.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Console.o: Console.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Console.o Console.cpp

${OBJECTDIR}/SplashScreen.o: SplashScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/SplashScreen.o SplashScreen.cpp

${OBJECTDIR}/GameLogger.o: GameLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/GameLogger.o GameLogger.cpp

${OBJECTDIR}/Game.o: Game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Game.o Game.cpp

${OBJECTDIR}/WoWBrain.o: WoWBrain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/WoWBrain.o WoWBrain.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/CardTest.o ${TESTDIR}/tests/CardTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcppunit -lcppunit -lcppunit 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/PlaneTest.o ${TESTDIR}/tests/PlaneTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lcppunit 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/WorldTest.o ${TESTDIR}/tests/WorldTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lcppunit 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/WoWBrainTest.o ${TESTDIR}/tests/WoWBrainTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} `pkg-config --libs cppunit`   


${TESTDIR}/tests/CardTest.o: tests/CardTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -w -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CardTest.o tests/CardTest.cpp


${TESTDIR}/tests/CardTestRunner.o: tests/CardTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -w -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CardTestRunner.o tests/CardTestRunner.cpp


${TESTDIR}/tests/PlaneTest.o: tests/PlaneTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -w -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/PlaneTest.o tests/PlaneTest.cpp


${TESTDIR}/tests/PlaneTestRunner.o: tests/PlaneTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -w -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/PlaneTestRunner.o tests/PlaneTestRunner.cpp


${TESTDIR}/tests/WorldTest.o: tests/WorldTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -w -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/WorldTest.o tests/WorldTest.cpp


${TESTDIR}/tests/WorldTestRunner.o: tests/WorldTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -w -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/WorldTestRunner.o tests/WorldTestRunner.cpp


${TESTDIR}/tests/WoWBrainTest.o: tests/WoWBrainTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -w -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/WoWBrainTest.o tests/WoWBrainTest.cpp


${TESTDIR}/tests/WoWBrainTestRunner.o: tests/WoWBrainTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -w -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/WoWBrainTestRunner.o tests/WoWBrainTestRunner.cpp


${OBJECTDIR}/World_nomain.o: ${OBJECTDIR}/World.o World.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/World.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/World_nomain.o World.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/World.o ${OBJECTDIR}/World_nomain.o;\
	fi

${OBJECTDIR}/Dialog_nomain.o: ${OBJECTDIR}/Dialog.o Dialog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Dialog.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Dialog_nomain.o Dialog.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Dialog.o ${OBJECTDIR}/Dialog_nomain.o;\
	fi

${OBJECTDIR}/Plane_nomain.o: ${OBJECTDIR}/Plane.o Plane.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Plane.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Plane_nomain.o Plane.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Plane.o ${OBJECTDIR}/Plane_nomain.o;\
	fi

${OBJECTDIR}/Card_nomain.o: ${OBJECTDIR}/Card.o Card.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Card.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Card_nomain.o Card.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Card.o ${OBJECTDIR}/Card_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/Console_nomain.o: ${OBJECTDIR}/Console.o Console.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Console.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Console_nomain.o Console.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Console.o ${OBJECTDIR}/Console_nomain.o;\
	fi

${OBJECTDIR}/SplashScreen_nomain.o: ${OBJECTDIR}/SplashScreen.o SplashScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SplashScreen.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SplashScreen_nomain.o SplashScreen.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SplashScreen.o ${OBJECTDIR}/SplashScreen_nomain.o;\
	fi

${OBJECTDIR}/GameLogger_nomain.o: ${OBJECTDIR}/GameLogger.o GameLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/GameLogger.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/GameLogger_nomain.o GameLogger.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/GameLogger.o ${OBJECTDIR}/GameLogger_nomain.o;\
	fi

${OBJECTDIR}/Game_nomain.o: ${OBJECTDIR}/Game.o Game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Game.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Game_nomain.o Game.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Game.o ${OBJECTDIR}/Game_nomain.o;\
	fi

${OBJECTDIR}/WoWBrain_nomain.o: ${OBJECTDIR}/WoWBrain.o WoWBrain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/WoWBrain.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -w -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/WoWBrain_nomain.o WoWBrain.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/WoWBrain.o ${OBJECTDIR}/WoWBrain_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wings-of-war

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
