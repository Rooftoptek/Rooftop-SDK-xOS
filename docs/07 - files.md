# Files

## The RTFile

`RTFile` lets you store application files in the cloud that would otherwise be too large or cumbersome to fit into a regular `RTObject`. The most common use case is storing images but you can also use it for documents, videos, music, and any other binary data (up to 10 megabytes).

Getting started with `RTFile` is easy. First, you'll need to have the data in `NSData` form and then create a `RTFile` with it. In this example, we'll just use a string:

<pre><code class="objectivec">
NSData *data = [@"Working at Rooftop is great!" dataUsingEncoding:NSUTF8StringEncoding];
RTFile *file = [RTFile fileWithName:@"resume.txt" data:data];
</code></pre>
<pre><code class="swift">
let str = "Working at Rooftop is great!"
let data = str.dataUsingEncoding(NSUTF8StringEncoding)
let file = RTFile(name:"resume.txt", data:data)
</code></pre>

Notice in this example that we give the file a name of `resume.txt`. There's two things to note here:

*   You don't need to worry about filename collisions. Each upload gets a unique identifier so there's no problem with uploading multiple files named `resume.txt`.
*   It's important that you give a name to the file that has a file extension. This lets Rooftop figure out the file type and handle it accordingly. So, if you're storing PNG images, make sure your filename ends with `.png`.

Next you'll want to save the file up to the cloud. As with `RTObject`, there are many variants of the `save` method you can use depending on what sort of callback and error handling suits you.

<pre><code class="objectivec">
[file saveInBackground];
</code></pre>
<pre><code class="swift">
file.saveInBackground()
</code></pre>

Finally, after the save completes, you can associate a `RTFile` onto a `RTObject` just like any other piece of data:

<pre><code class="objectivec">
RTObject *jobApplication = [RTObject objectWithClassName:@"JobApplication"]
jobApplication[@"applicantName"] = @"Joe Smith";
jobApplication[@"applicantResumeFile"] = file;
[jobApplication saveInBackground];
</code></pre>
<pre><code class="swift">
var jobApplication = RTObject(className:"JobApplication")
jobApplication["applicantName"] = "Joe Smith"
jobApplication["applicantResumeFile"] = file
jobApplication.saveInBackground()
</code></pre>

Retrieving it back involves calling one of the `getData` variants on the `RTFile`. Here we retrieve the resume file off another JobApplication object:

<pre><code class="objectivec">
RTFile *applicantResume = anotherApplication[@"applicantResumeFile"];
NSData *resumeData = [applicantResume getData];
</code></pre>
<pre><code class="swift">
let applicantResume = annotherApplication["applicationResumeFile"] as RTFile
let resumeData = applicantResume.getData()
</code></pre>

Just like on `RTObject`, you will most likely want to use the background version of `getData`.

## Images

You can easily store images by converting them to `NSData` and then using `RTFile`. Suppose you have a `UIImage` named `image` that you want to save as a `RTFile`:

<pre><code class="objectivec">
NSData *imageData = UIImagePNGRepresentation(image);
RTFile *imageFile = [RTFile fileWithName:@"image.png" data:imageData];

RTObject *userPhoto = [RTObject objectWithClassName:@"UserPhoto"];
userPhoto[@"imageName"] = @"My trip to Hawaii!";
userPhoto[@"imageFile"] = imageFile;
[userPhoto saveInBackground];
</code></pre>
<pre><code class="swift">
let imageData = UIImagePNGRepresentation(image)
let imageFile = RTFile(name:"image.png", data:imageData)

var userPhoto = RTObject(className:"UserPhoto")
userPhoto["imageName"] = "My trip to Hawaii!"
userPhoto["imageFile"] = imageFile
userPhoto.saveInBackground()
</code></pre>

Your `RTFile` will be uploaded as part of the save operation on the `userPhoto` object. It's also possible to track a `RTFile`'s [upload and download progress](#files-progress).

Retrieving the image back involves calling one of the `getData` variants on the `RTFile`. Here we retrieve the image file off another `UserPhoto` named `anotherPhoto`:

<pre><code class="objectivec">
RTFile *userImageFile = anotherPhoto[@"imageFile"];
[userImageFile getDataInBackgroundWithBlock:^(NSData *imageData, NSError *error) {
    if (!error) {
        UIImage *image = [UIImage imageWithData:imageData];
    }
}];
</code></pre>
<pre><code class="swift">
let userImageFile = anotherPhoto["imageFile"] as RTFile
userImageFile.getDataInBackgroundWithBlock {
  (imageData: NSData?, error: NSError?) -> Void in
  if error == nil {
    if let imageData = imageData {
        let image = UIImage(data:imageData)
    }
  }
}

</code></pre>

## Progress

It's easy to get the progress of both uploads and downloads using `RTFile` using `saveInBackgroundWithBlock:progressBlock:` and `getDataInBackgroundWithBlock:progressBlock:` respectively. For example:

<pre><code class="objectivec">
NSData *data = [@"Working at Rooftop is great!" dataUsingEncoding:NSUTF8StringEncoding];
RTFile *file = [RTFile fileWithName:@"resume.txt" data:data];
[file saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
  // Handle success or failure here ...
} progressBlock:^(int percentDone) {
  // Update your progress spinner here. percentDone will be between 0 and 100.
}];
</code></pre>
<pre><code class="swift">
let str = "Working at Rooftop is great!"
let data = str.dataUsingEncoding(NSUTF8StringEncoding)
let file = RTFile(name:"resume.txt", data:data)
file.saveInBackgroundWithBlock({
  (succeeded: Bool, error: NSError?) -> Void in
  // Handle success or failure here ...
}, progressBlock: {
  (percentDone: Int32) -> Void in
  // Update your progress spinner here. percentDone will be between 0 and 100.
})
</code></pre>

You can delete files that are referenced by objects using the [REST API](/docs/rest/guide#files-deleting-files). You will need to provide the master key in order to be allowed to delete a file.

If your files are not referenced by any object in your app, it is not possible to delete them through the REST API. You may request a cleanup of unused files in your app's Settings page. Keep in mind that doing so may break functionality which depended on accessing unreferenced files through their URL property. Files that are currently associated with an object will not be affected.


