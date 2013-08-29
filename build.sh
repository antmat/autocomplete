#!/bin/sh
UNAME=`uname`

if (which nproc 1>/dev/null 2>/dev/null)
then
JOB_CNT=`nproc`
fi;

if [ "$UNAME" = "Darwin" ]
then
        JOB_CNT=`sysctl hw.ncpu | awk '{print $2}'`
	MACOS_OPT="-D CMAKE_CXX_COMPILER=/opt/local/bin/g++"
else
	MACOS_OPT=""
fi
if [ "$1" = "all" ]
then
    JOB_CNT=$(($JOB_CNT/3+1))
fi
JOB_CNT="-j$JOB_CNT"
echo "################ Building with $JOB_CNT ###############"
#DEF_CXX="/usr/bin/g++-4.4"
#if [ -f "$DEF_CXX" ]
#then
#	OPTS="-D CMAKE_CXX_COMPILER=$DEF_CXX"
#fi
OPTS="$OPTS $2 $3 $4 $5 $6 $7 $8 $9 "
clean()
{
	DIR=$1 &&
	rm -fr ./${DIR} &&
	mkdir -p ${DIR}
}
clean_debug()
{
	clean "debug_build"
}
clean_release()
{
	clean "release_build"
}
#clean_profile()
#{
#	clean "profile_build"
#}
build()
{
	echo "******************************"
	echo "Building in $1"
	echo "******************************"
	DIR=$1
	mkdir -p $DIR
	cd ${DIR}
	cmake -D CMAKE_BUILD_TYPE=$2 $MACOS_OPT $OPTS ..
	if [ "$3" != "nowait" ]
	then
		make $JOB_CNT
	else
		make $JOB_CNT &
	fi
	cd ..
}
build_debug()
{
	build "debug_build" "Debug" $1
}
build_release()
{
	build "release_build" "Release" $1
}
#build_profile()
#{
#	build "profile_build" "Profile" $1
#}
case "$1" in
	clean)
		clean_debug
		clean_release
		#clean_profile
	;;
	clean-full)
		find . -name '*.o' -exec rm -rf {} \;
		find . -name '*.os' -exec rm -rf {} \;
		find . -name '*.a' -exec rm -rf {} \;
		find . -name '*.dylib' -exec rm -rf {} \;
		find . -name '*.so' -exec rm -rf {} \;
		find . -type d -name 'CMakeFiles' -exec rm -rf {} \;
		find . -name 'cmake_install.cmake' -exec rm -rf {} \;
		find . -name 'blizzard-server' -exec rm -rf {} \;
		rm -rf debug_build
		rm -rf release_build
		#rm -rf profile_build
	;;
	clean-cache)
		rm -rf cache/*
	;;
	#profile-full)
	#	clean_profile
	#	build_profile
	#;;
	#profile)
	#	build_profile
	#;;
	debug-full)
		clean_debug
		build_debug
	;;
	debug)
		build_debug
	;;
	release-full)
		clean_release
		build_release
	;;
	release)
		build_release
	;;
	all)
		build_debug "nowait"
		build_release "nowait"
		#build_profile "nowait"
                for i in `seq 1 600`
		do
			if ! (ps aux | grep make | grep -v grep 1> /dev/null 2>/dev/null)
			then
				break
			fi
			sleep 1
		done
	;;
	all-full)
		clean_debug
		clean_release
		#clean_profile
		build_debug
		build_release
		#build_profile
	;;
	package)
		svn up ../
		diff=`svn diff`
		if [ "$diff" != "" ]
		then
			echo "diff is not empty"
			exit 1
		fi

		dch -i 'new release'
		svn ci debian/changelog -m 'changelog commit'
		mkdir -p ../../old_packages
		mv ../../*.deb ../../*.changes ../../*.dsc ../../*.gz ../../old_packages
		export DEB_BUILD_OPTIONS="parallel=24"
		dpkg-buildpackage -b -j24
		mv ../*.deb ../*.changes ../*.dsc ../*.gz ../../
	;;
	*)
		echo "Usage: ./build.sh (clean|clean-full|debug|debug-full|release|release-full|clean-cache|package)"
		exit 1
	;;
esac
exit $?
