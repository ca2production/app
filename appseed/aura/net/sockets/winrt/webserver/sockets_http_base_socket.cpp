//#include "framework.h"
//#include "axis/compress/compress.h"


namespace sockets
{


   http_base_socket::http_base_socket(base_socket_handler& h) :
      ::object(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h)
   {

   }



   http_base_socket::~http_base_socket()
   {
   }


   void http_base_socket::OnFirst()
   {
      m_iContentLength = 0;
   }


   void http_base_socket::OnHeader(id key,const string & value)
   {

      http_socket::OnHeader(key, value);

      if(key == __id(content_length))
      {
         m_iContentLength = atoi(value);
      }

   }


   void http_base_socket::OnHeaderComplete()
   {
      http_socket::OnHeaderComplete();
      TRACE0("\n");
      TRACE0(m_request.attr("http_protocol").get_string() + "://" + m_request.header("host").get_string() + m_request.attr("request_uri").get_string() + "\n");
      if(m_request.attr("request_uri").get_string().find("/passthrough/") >= 0)
      {
         TRACE0( "Passthrought");
      }
      if(m_request.headers().has_property("user-agent"))
      {
         TRACE0("user-agent: " + m_request.header("user-agent") + "\n");
      }
      if(m_request.headers().has_property("from"))
      {
         TRACE0("from: " + m_request.header("from") + "\n");
      }
      if(m_request.headers().has_property("accept-language"))
      {
         TRACE0("accept-language: " + m_request.header("accept-language") + "\n");
      }
      if (m_body_size_left > 0)
      {
         m_request.InitBody( m_body_size_left );
      }
      else
      {
         // execute
         Execute();
      }
   }


   void http_base_socket::OnData(const char *buf,size_t sz)
   {
      m_request.write( buf, sz );
      m_body_size_left -= sz;
      if (!m_body_size_left)
      {
         m_request.CloseBody();

         // execute
         Execute();
      }
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Execute()
   {
      // parse form data / query_string and cookie header if available
      m_request.ParseBody();

      //TRACE("http version: %s\n", m_request.attr("http_version").get_string());
      //TRACE("connection: %s\n", m_request.header("connection").get_string());
      //TRACE("keepalive: %s\n", m_b_keepalive ? "true" : "false");
   /*   if(::str::ends(m_request.attr("http_version").get_string(), "/1.1")
         && m_request.header("connection").get_string().compare_ci("close") != 0)
      {
         m_b_keepalive = true;
      TRACE(" ***    keepalive: true\n");
      }
      else
      {
         m_b_keepalive = false;
         TRACE(" *** keepalive: false\n");
      }*/

      // prepare page
      OnExecute();

      Reset();
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Respond()
   {

      //TRACE0("http_base_socket::Respond");

      if(outheader(__id(content_type)).get_string().find("text") >= 0)
      {
      
         on_compress();

      }

      m_response.m_propertysetHeader.set(__id(content_length), (int64_t) m_response.file().get_length());

      for(int i = 0; i < m_response.cookies().get_size(); i++)
      {
      
         m_response.m_propertysetHeader.add(__id(set_cookie), m_response.cookies().element_at(i)->get_cookie_string());

      }

/* 

      if(m_response.m_propertysetHeader.low_has_property(__str(location)))
      {

         string strLocation = m_response.m_propertysetHeader.lowprop(__str(Location));

         m_response.m_propertysetHeader.remove_by_name("Location");

         m_response.m_propertysetHeader["Location"] = strLocation;

      }

*/

      SendResponse();

      if(m_obuf_top == NULL)
      {
         OnWriteComplete();
      }

      response().file().set_length(0);

   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::OnWriteComplete()
   {
      //Debug deb("http_base_socket::OnTransferLimit");
      //TRACE("\n");
      //TRACE("http_base_socket::OnTransferLimit\n");
   //   char msg[32768];
      OnResponseComplete();
      if (!m_b_keepalive)
      {
         //TRACE("SetCloseAndDelete\n");
         SetCloseAndDelete();
      }
      else
      {
         //TRACE("keep_alive\n");
      }
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Reset()
   {
      http_socket::Reset();
      m_body_size_left = 0;
   }


   void http_base_socket::OnResponseComplete()
   {
   }



   string http_base_socket::set_cookie(
         const char * name,
         var var,
         int iExpire,
         const char * path,
         const char * domain,
         bool bSecure)
   {
      m_request.cookies().set_cookie(
         name,
         var,
         iExpire,
         path,
         domain,
         bSecure);
      return m_response.cookies().set_cookie(
         name,
         var,
         iExpire,
         path,
         domain,
         bSecure);
   }

   void http_base_socket::on_compress()
   {
       
      if(inheader(__id(accept_encoding)).get_string().find("gzip") >= 0)
      {

         if(outheader(__id(content_type)).get_string().find_ci("text") >= 0)
         {
       
            m_response.m_propertysetHeader.set(__id(content_encoding), "gzip");

            ::memory_file file(get_app());

            ::gzip_stream gz(&file);

            gz.transfer_from(response().file());

            gz.finish();

            response().file().set_length(0);
            response().file().write(file.get_data(), file.get_size());

         }

      }

   }


} // namespace sockets
