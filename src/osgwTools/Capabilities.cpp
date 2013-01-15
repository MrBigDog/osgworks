/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * osgWorks is (C) Copyright 2009-2012 by Kenneth Mark Bryden
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include <osgwTools/Capabilities.h>
#include <osgwTools/Version.h>

#include <osg/Version>
#include <osg/GL>
#include <osg/GL2Extensions>
#include <osg/Texture3D>
#include <osg/TextureCubeMap>
#include <osg/FragmentProgram>


namespace osgwTools
{


Capabilities::Capabilities( osg::GraphicsContext* gc )
{
    _osgWorksVersion = osgwTools::getVersionString();
    _osgVersion = osgGetVersion();

    _glVersion = (const char*)( glGetString( GL_VERSION ) );
    _glVendor = (const char*)( glGetString( GL_VENDOR ) );
    _glRenderer = (const char*)( glGetString( GL_RENDERER ) );

    if( gc == NULL )
    {
        osg::notify( osg::WARN ) << "Must specify a non-NULL GC." << std::endl;
        _glslVersion = 0.f;
    }
    else
    {
        unsigned int id = gc->getState()->getContextID();
        const osg::GL2Extensions* gl2 = osg::GL2Extensions::Get( id, true );
        _glslVersion = gl2->getLanguageVersion();
    }

    glGetIntegerv( GL_MAX_TEXTURE_SIZE, &_texSize );
    glGetIntegerv( GL_MAX_3D_TEXTURE_SIZE, &_3DTexSize );
    glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &_cubeMapTexSize );
    glGetIntegerv( GL_MAX_TEXTURE_UNITS, &_maxTexUnits );

    glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &_shaderUnits );
    glGetIntegerv( GL_MAX_TEXTURE_COORDS_ARB, &_texCoords );
    glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &_vertexAttribs );
    glGetIntegerv( GL_MAX_DRAW_BUFFERS, &_drawBuffers );
}
Capabilities::~Capabilities()
{
}

void Capabilities::dump( std::ostream& ostr )
{
    ostr << _osgWorksVersion << std::endl;
    ostr << "OSG version: " << _osgVersion << std::endl;

    ostr << "  Queriable strings ----------------------------------------" << std::endl;
    ostr << "    GL_VERSION: " << _glVersion << std::endl;
    ostr << "    GL_VENDOR: " << _glVendor << std::endl;
    ostr << "    GL_RENDERER: " << _glRenderer << std::endl;
    ostr << "    GLSL version: " << _glslVersion << std::endl;

    ostr << "  Texture implementation constants -------------------------" << std::endl;
    ostr << "    GL_MAX_TEXTURE_SIZE: " << _texSize << std::endl;
    ostr << "    GL_MAX_3D_TEXTURE_SIZE: " << _3DTexSize << std::endl;
    ostr << "    GL_MAX_CUBE_MAP_TEXTURE_SIZE: " << _cubeMapTexSize << std::endl;
    ostr << "    GL_MAX_TEXTURE_UNITS: " << _maxTexUnits << std::endl;

    ostr << "  Shader implementation constants --------------------------" << std::endl;
    ostr << "    GL_MAX_TEXTURE_IMAGE_UNITS: " << _shaderUnits << std::endl;
    ostr << "    GL_MAX_TEXTURE_COORDS: " << _texCoords << std::endl;
    ostr << "    GL_MAX_VERTEX_ATTRIBS: " << _vertexAttribs << std::endl;
    ostr << "    GL_DRAW_BUFFERS: " << _drawBuffers << std::endl;
}


// namespace osgwTools
}