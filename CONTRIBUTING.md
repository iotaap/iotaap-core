# Contributing

Let's create together! We want to make contributing to this project as easy and transparent as possible, whether it's:

- Reporting a bug
- Discussing the current state of the code
- Submitting a fix
- Proposing new features
- Becoming a maintainer

## Kanban

Check our [Kanban](https://github.com/orgs/mvtsolutions/projects/1), all tasks in Kanban are prioritized. If you want to add a new task 
please submit a new issue with the appropriate label to "IoTaaP Firmware" project.

## Pull Request Process

All code changes happen through pull requests.

1. Fork the repo
2. Create your feature branch (`git checkout -b feature/spaceship`)
3. Make your changes and test your code
4. Generate new documentation using [Doxygen](http://www.doxygen.nl/download.html) and put it in "docs" directory
    * This is not mandatory, but it's helpful
    * Doxyfile and footer are located under "docs" directory
5. Update CHANGELOG
6. Commit your changes (`git commit -am 'Add spaceship feature'`)
7. Push to the branch (`git push origin feature/spaceship`)
8. Create a new Pull Request

## Conventions

Keep it consistent!

### Standards

- Main IoTaaP class is always located under src/IoTaaP.cpp and it should only contain the constructor
- IoTaaP.h must include all local libs
- Special Feature is a feature that is not required by default and it's memory critical (too big to be compiled if not required, e.g. ArduinoJson or BluetoothSerial)
    - Every special feature inside IoTaaP.h must have #ifdef ENABLE_FEATURENAME #endif pair
    - Every special feature COMMENTED #define directive (e.g. //#define ENABLE_BTSERIAL) must be put into SpecialFeatures.h file
- Dedicated IoTaaP libs should be put inside src/lib/iotaap/<iotaap_featurename>
- 3rd party libs should be put inside src/lib/3rd_party/<FeatureDirectory>
- Under <iotaap_featurename> directory put .cpp and .h files using the following naming convention: <IoTaaP_FeatureName.cpp>
- Under IoTaaP.h create object of the feature using the following convention: IoTaaP_FeatureName featureName
- If possible (e.g. no dependency issues) include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h" in your file, instead of including (e.g.) Arduino.h, etc.
- Document your code using [Doxygen](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen)
- Doxygen documentation should contain only HTML version
- Generated documentation files should be put into "docs" directory using the following convention: /docs/<yyyy-mm-dd_FeatureName> 

## Report bugs using Github's issues
We use GitHub issues to track bugs. Report a bug by opening a new issue.

## Write bug reports with detail, background, and sample code
Be clear and informative

**Great Bug Reports** tend to have:

- A quick summary and/or background
- Steps to reproduce
  - Be specific!
  - Give sample code if you can.
- What you expected would happen
- What actually happens
- Notes (possibly including why you think this might be happening, or stuff you tried that didn't work)

## Use a Consistent Coding Style
Format your code before pushing any changes

## License
By contributing, you agree that your contributions will be licensed under GNU General Public License.