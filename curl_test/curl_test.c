
#include <stdio.h>

#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/types.h>


#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

int my_progress_func(void *v, double dltotal, double dlnow, double ultotal, double ulnow)
{
  printf("Current progress = %f, %f, %f, %f\n", 
      dltotal, dlnow, ultotal, ulnow);

  return 0;
}

int main()
{
  CURL *curl;
  int ret;
  
  curl = curl_easy_init();

  if (!curl) {
    // FIXME error handling
    return -1;
  }
  
  curl_easy_setopt(curl, CURLOPT_URL, "http://www.precisionplanting.com/trials2020/fileupload.php");
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
  curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, my_progress_func);

  struct curl_httppost *post=NULL;
  struct curl_httppost *last=NULL;

  ret = curl_formadd(&post, &last,
      CURLFORM_COPYNAME, "name_first",
      CURLFORM_COPYCONTENTS, "Cliff",
      CURLFORM_END);

  ret = curl_formadd(&post, &last,
      CURLFORM_COPYNAME, "name_last",
      CURLFORM_COPYCONTENTS, "Farmer Brake",
      CURLFORM_END);

  ret = curl_formadd(&post, &last,
      CURLFORM_COPYNAME, "file",
      CURLFORM_FILE, "test.txt",
      CURLFORM_END);

  ret = curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);

  ret = curl_easy_perform(curl);

  curl_formfree(post);
}


