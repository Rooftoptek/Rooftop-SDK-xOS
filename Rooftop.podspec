Pod::Spec.new do |s|
  s.name         = "Rooftop"
  s.version      = "0.5.0"
  s.summary      = "Rooftop SDK for Apple platforms"
  s.description  = "Rooftop SDK for Apple platforms."
  s.authors      = "RFTP Technologies Ltd"
  s.homepage     = "https://www.rftp.io"
  s.license      = { :type => 'Commercial', :file => 'LICENSE' }
  s.source       = { :git => "https://github.com/Rooftoptek/Rooftop-SDK-xOS.git", :tag => s.version.to_s }

  s.libraries      = 'sqlite3'
  s.dependency 'Bolts/Tasks', '~> 1.8.0'

  s.ios.frameworks = 'AudioToolbox',
                     'CoreLocation',
                     'SystemConfiguration'

  s.ios.deployment_target  = '9.0'
  s.ios.vendored_framework = 'iOS/Rooftop.framework'
  s.ios.dependency 'AWSCognito', '~> 2.5.0'
  s.ios.dependency 'AWSLambda', '~> 2.5.0'
  s.ios.dependency 'AWSS3', '~> 2.5.0'

  s.tvos.deployment_target  = '9.0'
  s.tvos.vendored_framework = 'tvOS/Rooftop.framework',
                              'tvOS/AWSCore.framework',
                              'tvOS/AWSCognito.framework',
                              'tvOS/AWSLambda.framework',
                              'tvOS/AWSS3.framework'

  s.watchos.deployment_target  = '3.0'
  s.watchos.vendored_framework = 'watchOS/Rooftop.framework',
                                 'watchOS/AWSCore.framework',
                                 'watchOS/AWSCognito.framework',
                                 'watchOS/AWSLambda.framework',
                                 'watchOS/AWSS3.framework'

  s.osx.deployment_target  = '10.9'
  s.osx.vendored_framework = 'macOS/Rooftop.framework',
                                 'macOS/AWSCore.framework',
                                 'macOS/AWSCognito.framework',
                                 'macOS/AWSLambda.framework',
                                 'macOS/AWSS3.framework'
end
