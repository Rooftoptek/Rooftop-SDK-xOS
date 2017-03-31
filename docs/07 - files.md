# Files

## The RTFile

`RTFile` lets you store application files in the cloud that would otherwise be too large or cumbersome to fit into a regular `RTObject`. The most common use case is storing images but you can also use it for documents, videos, music, and any other binary data (up to 10 megabytes).

Getting started with `RTFile` is easy. First, you'll need to have the data in `NSData` form and then create a `RTFile` with it. In this example, we'll just use a string:

### Objective - C
<pre><code class="objectivec">NSData *data = [@"Working at Rooftop is great!" dataUsingEncoding:NSUTF8StringEncoding];
RTFile *file = [RTFile setContentFromData:data];
</code></pre>

### Swift
<pre><code class="swift">let str = "Working at Rooftop is great!"
let data = str.data(using: String.Encoding.utf8)
let file = RTFile()
file.setContentFrom(data!)
</code></pre>

Next you'll want to save the file up to the cloud. As with `RTObject`, there are many variants of the `save` method you can use depending on what sort of callback and error handling suits you.

### Objective - C
<pre><code class="objectivec">[file saveInBackground];
</code></pre>

### Swift
<pre><code class="swift">file.saveInBackground()
</code></pre>

Finally, after the save completes, you can associate a `RTFile` onto a `RTObject` just like any other piece of data:

### Objective - C
<pre><code class="objectivec">RTObject *jobApplication = [RTObject objectWithClassName:@"JobApplication"]
jobApplication[@"applicantName"] = @"Joe Smith";
jobApplication[@"applicantResumeFile"] = file;
[jobApplication saveInBackground];
</code></pre>

### Swift
<pre><code class="swift">var jobApplication = RTObject(className:"JobApplication")
jobApplication["applicantName"] = "Joe Smith"
jobApplication["applicantResumeFile"] = file
jobApplication.saveInBackground()
</code></pre>

Retrieving it back involves calling one of the `getData` variants on the `RTFile`. Here we retrieve the resume file off another JobApplication object:

### Objective - C
<pre><code class="objectivec">RTFile *applicantResume = anotherApplication[@"applicantResumeFile"];
NSData *resumeData = [applicantResume getData];
</code></pre>

### Swift
<pre><code class="swift">let applicantResume = annotherApplication["applicationResumeFile"] as RTFile
let resumeData = applicantResume.getData()
</code></pre>

Just like on `RTObject`, you will most likely want to use the background version of `getData`.

## Images

You can easily store images by converting them to `NSData` and then using `RTFile`. Suppose you have a `UIImage` named `image` that you want to save as a `RTFile`:

### Objective - C
<pre><code class="objectivec">NSData *imageData = UIImagePNGRepresentation(image);
RTFile *imageFile = [RTFile fileWithName:@"image.png" data:imageData];

RTObject *userPhoto = [RTObject objectWithClassName:@"UserPhoto"];
userPhoto[@"imageName"] = @"My trip to Hawaii!";
userPhoto[@"imageFile"] = imageFile;
[userPhoto saveInBackground];
</code></pre>

### Swift
<pre><code class="swift">let imageData = UIImagePNGRepresentation(image)
let imageFile = RTFile(name:"image.png", data:imageData)

var userPhoto = RTObject(className:"UserPhoto")
userPhoto["imageName"] = "My trip to Hawaii!"
userPhoto["imageFile"] = imageFile
userPhoto.saveInBackground()
</code></pre>

Your `RTFile` will be uploaded as part of the save operation on the `userPhoto` object. It's also possible to track a `RTFile`'s upload and download progress.

Retrieving the image back involves calling one of the `getData` variants on the `RTFile`. Here we retrieve the image file off another `UserPhoto` named `anotherPhoto`:

### Objective - C
<pre><code class="objectivec">RTFile *userImageFile = anotherPhoto[@"imageFile"];
[userImageFile getDataInBackgroundWithBlock:^(NSData *imageData, NSError *error) {
    if (!error) {
        UIImage *image = [UIImage imageWithData:imageData];
    }
}];
</code></pre>

### Swift
<pre><code class="swift">let userImageFile = anotherPhoto["imageFile"] as RTFile
file.getDataInBackground { (success, error) in
  if error == nil {
    if let imageData = imageData {
        let image = UIImage(data:imageData)
    }
  }
}

</code></pre>

## Progress

It's easy to get the progress of both uploads and downloads using `RTFile` using `saveInBackgroundWithBlock:progressBlock:` and `getDataInBackgroundWithBlock:progressBlock:` respectively. For example:

### Objective - C
<pre><code class="objectivec">NSData *data = [@"Working at Rooftop is great!" dataUsingEncoding:NSUTF8StringEncoding];
RTFile *file = [RTFile setContentFromData:data];
[file saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
  // Handle success or failure here ...
} progressBlock:^(int percentDone) {
  // Update your progress spinner here. percentDone will be between 0 and 100.
}];
</code></pre>

### Swift
<pre><code class="swift">let str = "Working at Rooftop is great!"
let data = str.dataUsingEncoding(NSUTF8StringEncoding)
let file = RTFile()
file.setContentFrom(data!)
file.saveInBackground { (progress) in
  // Update your progress spinner here. percentDone will be between 0 and 100.
}
</code></pre>