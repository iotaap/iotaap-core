# Contributing

Let's create together! We want to make contributing to this project as easy and transparent as possible, whether it's:

- Reporting a bug
- Discussing the current state of the code
- Submitting a fix
- Proposing new features
- Becoming a maintainer

## Pull Request Process

All code changes happen through pull requests.

1. Fork the repo
2. Create your branch from **master** (`git checkout -b feature/spaceship`)
3. Make your changes and test your code
4. Commit your changes (`git commit -am 'Add spaceship feature'`)
5. Push to the branch (`git push origin feature/spaceship`)
6. Create a new Pull Request to the **dev** branch

## After PR

Your PR will be reviewed by us and it must pass various predefined tests, finally, your PR will be merged with our **dev** branch. Once
in a while we merge **dev** and **master** branches and create a new release. We will handle version updating, final CHANGELOG, and similar
procedures.

## Conventions

Keep it consistent!

### Standards

- Main IoTaaP class is always located under src/IoTaaP.cpp and it should only contain the constructor
- IoTaaP.h must include all local libs
- Dedicated IoTaaP libs should be put inside src/lib/iotaap/<iotaap_featurename>
- 3rd party libs should be defined in library.json
- Under <iotaap_featurename> directory put .cpp and .h files using the following naming convention: <IoTaaP_FeatureName.cpp>
- Under IoTaaP.h create object of the feature using the following convention: IoTaaP_FeatureName featureName
- If possible (e.g. no dependency issues) include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h" in your file, instead of including (e.g.) Arduino.h, etc.
- Document your code (explain what you did and how it works)

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
By contributing, you agree that your contributions will be licensed under Apache License 2.0, see [LICENSE](./LICENSE.md).