pipeline {
  agent any
  stages {
    stage('Prepare') {
      steps {
        sh '''pip install -U platformio
python3 -m platformio update
python3 -m platformio platform install espressif32
python3 -m platformio lib -g install ./'''
      }
    }

    stage('Bulid examples') {
      parallel {
        stage('Bulid first example') {
          steps {
            sh 'python3 -m platformio ci --lib="." --board="esp32dev" /home/iotaap-jenkins/pio_test/iotaap-core/examples/InitialCode'
          }
        }

        stage('') {
          steps {
            sh 'python3 -m platformio ci --lib="." --board="esp32dev" /home/iotaap-jenkins/pio_test/iotaap-core/examples/IoTaaP-WiFi'
          }
        }

        stage('Build second example') {
          steps {
            sh 'python3 -m platformio ci --lib="." --board="esp32dev" /home/iotaap-jenkins/pio_test/iotaap-core/examples/IoTaaP-WiFi'
          }
        }

      }
    }

    stage('') {
      steps {
        echo 'Finished'
      }
    }

  }
}