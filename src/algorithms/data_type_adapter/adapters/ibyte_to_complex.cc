/*!
 * \file ibyte_to_complex.cc
 * \brief Adapts an I/Q interleaved byte integer sample stream to a gr_complex (float) stream
 * \author Javier Arribas, jarribas(at)cttc.es
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#include "ibyte_to_complex.h"
#include <glog/logging.h>
#include "configuration_interface.h"

using google::LogMessage;

IbyteToComplex::IbyteToComplex(ConfigurationInterface* configuration, std::string role,
        unsigned int in_streams, unsigned int out_streams) :
                config_(configuration), role_(role), in_streams_(in_streams),
                out_streams_(out_streams)
{
    std::string default_input_item_type = "byte";
    std::string default_output_item_type = "gr_complex";
    std::string default_dump_filename = "../data/input_filter.dat";

    DLOG(INFO) << "role " << role_;

    input_item_type_ = config_->property(role_ + ".input_item_type", default_input_item_type);

    dump_ = config_->property(role_ + ".dump", false);
    dump_filename_ = config_->property(role_ + ".dump_filename", default_dump_filename);

    size_t item_size = sizeof(gr_complex);

    gr_interleaved_char_to_complex_ = gr::blocks::interleaved_char_to_complex::make();

    DLOG(INFO) << "data_type_adapter_(" << gr_interleaved_char_to_complex_->unique_id() << ")";

    if (dump_)
        {
            DLOG(INFO) << "Dumping output into file " << dump_filename_;
            file_sink_ = gr::blocks::file_sink::make(item_size, dump_filename_.c_str());
        }
}


IbyteToComplex::~IbyteToComplex()
{}


void IbyteToComplex::connect(gr::top_block_sptr top_block)
{
    if (dump_)
        {
            top_block->connect(gr_interleaved_char_to_complex_, 0, file_sink_, 0);
        }
}


void IbyteToComplex::disconnect(gr::top_block_sptr top_block)
{
    if (dump_)
        {
            top_block->disconnect(gr_interleaved_char_to_complex_, 0, file_sink_, 0);
        }
}



gr::basic_block_sptr IbyteToComplex::get_left_block()
{
    return gr_interleaved_char_to_complex_;
}



gr::basic_block_sptr IbyteToComplex::get_right_block()
{
    return gr_interleaved_char_to_complex_;
}


