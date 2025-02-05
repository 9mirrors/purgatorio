pipeline {
	agent {
		kubernetes {
				cloud 'sm0'
				inheritFrom 'Debian'
				namespace 'jenkins'
			}
		}


	stages {
		stage('Build') {
			steps {
				sh 'dpkg --add-architecture i386'
				sh 'apt update'
				sh 'apt upgrade -y'
				sh 'apt install -y gcc-multilib libx11-6:i386 libxext6:i386 libx11-dev:i386 libxext-dev:i386'
				sh 'sed -i -e "s@^ROOT=.*@ROOT=$(readlink -f .)@" mkconfig'
				sh './makemk.sh'
				sh 'env PATH="$(readlink -f Linux/386/bin):${PATH}" mk mkdirs'
				sh 'env PATH="$(readlink -f Linux/386/bin):${PATH}" mk nuke'
				sh 'env PATH="$(readlink -f Linux/386/bin):${PATH}" mk install'
				sh 'git log -n1 --pretty=%H > BUILD-COMMIT'
				sh 'mkdir -p /tmp && tar zcf /tmp/purgatorio.tar.gz --exclude .git .'
				sh 'mv /tmp/purgatorio.tar.gz .'
				archiveArtifacts artifacts: 'purgatorio.tar.gz', fingerprint: true
			}
		}
	}
}
