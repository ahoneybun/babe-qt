


document.addEventListener('DOMContentLoaded', function() 
{
  var babeBtn = document.getElementById('babe');
  
  babeBtn.addEventListener('click', function() 
  {

    chrome.tabs.getSelected(null, function(tab) 
    {
      d = document;
      var url =tab.url;
      var ydoc= tab.title;
      console.log(ydoc);
      if(url.includes("youtube.com/watch?v"))
      {
          var newStr = url.substring(url.lastIndexOf("watch?v=")+8,url.length);
          
           if(newStr.includes("&"))
           {
               console.log("the string inclues ambersan");
              newStr = newStr.substring(0,newStr.indexOf("&"));
           }
           
          
 /*var title = document.getElementById('title').value;
          var artist = document.getElementById('artist').value;
          var album = document.getElementById('album').value;
          var info = "[title] = "+title+"\n[artist] = "+artist+"\n[album] = "+album;
          console.log(info);          */
          download(newStr, newStr+'.babe', 'text/plain');
          chrome.browserAction.setIcon({path: "icon_done.png"});
          
        }else
        { 
            console.log("url does not contains yuotube");
            
            document.getElementById("warning").innerHTML+= "This isn't a YouTube url";
        }
        
    });
  }, false);
  
  
  /*var optionsBtn = document.getElementById('optionsBtn');
   optionsBtn.addEventListener('click', function() 
  {
console.log("options btn clicked");
document.getElementById("optionsBtn").style.visibility="show";
   
  }, false);*/
  
}, false);




function download(strData, strFileName, strMimeType) {
    var D = document,
        A = arguments,
        a = D.createElement("a"),
        d = A[0],
        n = A[1],
        t = A[2] || "text/plain";

    //build download link:
    a.href = "data:" + strMimeType + "charset=utf-8," + escape(strData);


    if (window.MSBlobBuilder) { // IE10
        var bb = new MSBlobBuilder();
        bb.append(strData);
        return navigator.msSaveBlob(bb, strFileName);
    } /* end if(window.MSBlobBuilder) */



    if ('download' in a) { //FF20, CH19
        a.setAttribute("download", n);
      /* a.innerHTML = "downloading...";*/
        D.body.appendChild(a);
        setTimeout(function() {
            var e = D.createEvent("MouseEvents");
            e.initMouseEvent("click", true, false, window, 0, 0, 0, 0, 0, false, false, false, false, 0, null);
            a.dispatchEvent(e);
            D.body.removeChild(a);
        }, 66);
        return true;
    }; /* end if('download' in a) */



    //do iframe dataURL download: (older W3)
    var f = D.createElement("iframe");
    D.body.appendChild(f);
    f.src = "data:" + (A[2] ? A[2] : "application/octet-stream") + (window.btoa ? ";base64" : "") + "," + (window.btoa ? window.btoa : escape)(strData);
    setTimeout(function() {
        D.body.removeChild(f);
    }, 333);
    return true;
}
