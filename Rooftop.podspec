Pod::Spec.new do |s|
  s.name         = "Rooftop"
  s.version      = "0.5.0"
  s.summary      = "Rooftop SDK for Apple platforms"
  s.description  = "Rooftop SDK for Apple platforms."
  s.authors      = "RFTP Technologies Ltd"
  s.homepage     = "https://www.rftp.io"
  s.license      = { :type => 'Commercial', :file => 'LICENSE' }
  s.source       = { :git => "https://github.com/Rooftoptek/Rooftop-SDK-xOS.git", :tag => s.version.to_s }

  s.platform = :ios
  s.ios.deployment_target = '9.0'
  s.ios.vendored_framework = 'iOS/Rooftop.framework'

  s.ios.frameworks = 'AudioToolbox',
                     'CoreLocation',
                     'SystemConfiguration'
  s.libraries      = 'sqlite3'

  s.dependency 'Bolts/Tasks', '~> 1.8.0'
  s.dependency 'AWSCognito', '~> 2.4.0'
  s.dependency 'AWSLambda', '~> 2.4.0'
  s.dependency 'AWSS3', '~> 2.4.0'
end
