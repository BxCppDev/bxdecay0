#!/usr/bin/env python3

import sys

def save_tab_cdf(cprobs_, ndigits_, out_) :
    count = 0
    cur9 = -1
    bias9 = 1.0 - 10**(-cur9)
    first = True
    float_fmt="{:." + "{:d}".format(ndigits_) + 'g}'
    #print('[debug] float_fmt=', float_fmt, file=sys.stderr)
    while count < len(cprobs_) :
        cprob = cprobs_[count]
        this9 = 0
        one = False
        if   cprob < 0.9 :
            this9 = 0
        elif cprob < 0.99 :
            this9 = 1
        elif cprob < 0.999 :
            this9 = 2
        elif cprob < 0.9999 :
            this9 = 3
        elif cprob < 0.99999 :
            this9 = 4
        elif cprob < 0.999999 :
            this9 = 5
        elif cprob < 0.9999999 :
            this9 = 6
        elif cprob < 0.99999999 :
            this9 = 7
        elif cprob < 0.999999999 :
            this9 = 8
        elif cprob < 0.9999999999 :
            this9 = 9
        elif cprob < 0.99999999999 :
            this9 = 10
        elif cprob < 0.999999999999 :
            this9 = 11
        elif cprob < 0.9999999999999 :
            this9 = 12
        elif cprob < 0.99999999999999 :
            this9 = 13
        elif cprob < 0.999999999999999 :
            this9 = 14
        elif cprob < 0.9999999999999999 :
            this9 = 15
        else :
            one = True
        #print("[debug] bias9 = ", bias9, file=sys.stderr)
        if this9 > cur9 :
            cur9 = this9
            bias9 = 1.0 - 10**(-cur9)
            if not first :
                out_.write(" ")
            out_.write("^{:d}".format(cur9))
            first = False
        if not first :
            out_.write(" ")
            first = False
        if one :
            out_.write("!1")
        else :
            # p = int((cprob - bias9) * 10**(cur9+1+ndigits_))
            # print("[debug] p = ", p, file=sys.stderr)
            # out_.write("{:d}".format(p))            
            p = (cprob - bias9) * 10**(cur9+1)
            #print("[debug] p = ", p, file=sys.stderr)
            out_.write(float_fmt.format(p))            
        count += 1
    out_.write('\n')
    return

class mkocdfdata :

    def __init__(self, pdf_filename_, isotope_, dbd_ga_mode_, qbb_, debug_ = False) :
        if len(isotope_.strip()) == 0 :
            raise Exception("Invalid isotope!")
        self.isotope = isotope_
        if not dbd_ga_mode_ in ["g0", "g2", "g22", "g4"] :
            raise Exception("Invalid DBD gA mode!")
        self.dbd_ga_mode = dbd_ga_mode_
        if qbb_ < 0.0 :
            raise Exception("Invalid Qbb value!")
        self.qbb = qbb_
        self.pdf_filename = pdf_filename_
        self.opdf_filename = "tab_pdf.data"
        self.debug = debug_
        self.ncdf_filename = "tab_ocdf.data"
        # Tabulated p.d.f. data:
        self.tab_pdf = []
        self.e1min =-1.0
        self.e1max =-1.0
        self.ne1   = -1
        self.ne2   = -1
        self.estep = -1
        # Tabulated c.d.f. data:
        self.tab_cdf = []
        # Tabulated normalize c.d.f. data:
        self.tab_ncdf = []
        return
    
    def load_tab_pdf(self) :
        debug = self.debug
        debug = False
        fpdf = open(self.pdf_filename, "r")
        rawlines = fpdf.readlines()
        count_lines = 0
        current_e1 = -1.0
        current_probs = []
        for rawline in rawlines :
            count_lines += 1
            line = rawline[:-1].strip()
            if debug and count_lines <= 10 :
                print("[debug] Line #{} : <{}>".format(count_lines, line), file=sys.stderr)
            tokens = line.split()
            if debug and count_lines <= 10 :
                print("tokens : {}".format(tokens), file=sys.stderr)
            e1 = float(tokens[0])
            e2 = float(tokens[1])
            dpde1de2 = float(tokens[2])
            if debug and count_lines <= 10 :
                print("[debug] e1 : {}".format(e1), file=sys.stderr)
                print("[debug] e2 : {}".format(e2), file=sys.stderr)
                print("[debug] dpde1de2 : {}".format(dpde1de2), file=sys.stderr)   
            if current_e1 < 0.0 :
                if debug :
                    print("[debug] First e1 sample: {}".format(e1), file=sys.stderr)
                current_e1 = e1
                self.e1min = e1
                self.e1max = e1
            if e1 > current_e1 :
                if debug :
                    print("[debug] New e1 sample: {}".format(e1), file=sys.stderr)
                self.tab_pdf.append(current_probs)
                if self.ne2 < 0 :
                    self.ne2 = len(current_probs)
                current_probs = []
                current_e1 = e1           
                if self.e1min < 0.0 or e1 < self.e1min :
                    self.e1min = e1
                if self.e1max < 0.0 or e1 > self.e1max :
                    self.e1max = e1
            current_probs.append(dpde1de2)
        self.tab_pdf.append(current_probs)
        self.ne1 = len(self.tab_pdf)
        self.estep=(self.e1max - self.e1min) / (self.ne2 - 1)
        if debug :
            print("[debug] ne1    = {}".format(self.ne1), file=sys.stderr)
            print("[debug] ne2    = {}".format(self.ne2), file=sys.stderr)
            print("[debug] e1min  = {} MeV".format(self.e1min), file=sys.stderr)
            print("[debug] e1max  = {} MeV".format(self.e1max), file=sys.stderr)
            print("[debug] estep  = {} MeV".format(self.estep), file=sys.stderr)
        return
    
    def print_tab_pdf(self, out_ = sys.stderr) :
        out_.write("NE1 = {:d}\n".format(self.ne1))
        out_.write("NE2 = {:d}\n".format(self.ne2))
        out_.write("E min = {:.5e} MeV\n".format(self.e1min))
        out_.write("E max = {:.5e} MeV\n".format(self.e1max))
        out_.write("E step = {:.5e} MeV\n".format(self.estep))
        out_.write("Tabulated p.d.f :\n")
        for i in range(len(self.tab_pdf)) :
            e1i = self.e1min + i * self.estep
            out_.write("{:d} E1={:.5e} MeV : ".format(i, e1i))
            out_.write("{:d} prob. samples from {:.6e} to {:.6e} "
                       .format(len(self.tab_pdf[i]),self.tab_pdf[i][0],self.tab_pdf[i][-1]))
            out_.write("\n")
        return
        
    def save_tab_pdf(self, deco_ = False):
        prob_eps=1e-7
        opdf_filename = self.opdf_filename
        ftabpdf = open(opdf_filename, "w")
        ftabpdf.write("#isotope={}\n".format(self.isotope))
        ftabpdf.write("#dbd_ga.mode={}\n".format(self.dbd_ga_mode))
        ftabpdf.write("{:.4f}\n".format(self.qbb))
        ftabpdf.write("Probability {:.16e} {:.16e} {:.16e} {:d}\n"
                      .format(self.e1min, self.e1max, self.estep, self.ne1))
        for i in range(len(self.tab_pdf)) :
            e1i = self.e1min + i * self.estep
            if deco_ :
                ftabpdf.write("\n\n#e1={:.16e}\n".format(e1i))
            n2 = len(self.tab_pdf[i])
            for j in range(n2) :
                ftabpdf.write("{:.7e} ".format(self.tab_pdf[i][j]))
            ftabpdf.write("\n")
        ftabpdf.close()  
        return
        
    def fill_tab_cdf(self) :
        self.tab_cdf = []
        for i in range(len(self.tab_pdf)) :
            se2 = self.tab_pdf[i]
            e1i = self.e1min + i * self.estep
            e2max = self.qbb - e1i
            de1i = self.estep
            if i == 0 :
                de1i = self.e1min
            e1_sumpdf = 0.0
            sumpdfs = []
            for j in range(len(se2)):
                e2j = self.e1min + j * self.estep
                de2j = self.estep
                if j == 0 :
                    de2j = self.e1min
                integral_pdf = se2[j] * de1i * de2j
                if i == 0 and j == len(se2) - 1:
                    print("[debug] i={} j={} e1={} e2={} int_pdf={}"
                          .format(i, j, e1i, e2j, integral_pdf), file=sys.stderr)   
                e1_sumpdf += integral_pdf
                sumpdfs.append(e1_sumpdf)
            # First-order end-point correction:
            # if i == 0 :
            #     de2j = qbb_ - e2j 
            #     endpoint_int_pdf = int_pdf * de1i * de2j / 2
            # else :
            #     endpoint_int_pdf = int_pdf * de1i * de2j / 2
            # e1_sumpdf += endpoint_int_pdf
            self.tab_cdf.append((e1_sumpdf, sumpdfs))
    
    def print_tab_cdf(self, out_ = sys.stderr) :
        out_.write("Tabulated c.d.f :\n")
        for i in range(len(self.tab_cdf)) :
            e1i = self.e1min + i * self.estep
            out_.write("{:d} E1={:.5e} MeV : ".format(i, e1i))
            out_.write("Cumul tot prob={:.16e} : ".format(self.tab_cdf[i][0]))
            out_.write("=>  {:d} cumul prob. samples from {:.16e} to {:.16e} "
                       .format(len(self.tab_cdf[i][1]),self.tab_cdf[i][1][0],self.tab_cdf[i][1][-1]))
            out_.write("\n")
        return
       
    def fill_tab_ncdf(self) :
        self.tab_ncdf = []
        tot_sumcdf = 0.0
        for i in range(len(self.tab_cdf) -1, -1, -1) :
            e1_sumpdf = self.tab_cdf[i][0]
            tot_sumcdf += e1_sumpdf            
        sys.stderr.write("[debug] tot_sumcdf={}\n".format(tot_sumcdf))
        for i in range(len(self.tab_cdf)) :
            e1_sumpdf = self.tab_cdf[i][0]
            sumpdfs = self.tab_cdf[i][1]
            norm_sumpdfs = []
            for j in range(len(sumpdfs)) :
                norm_sumpdfs.append(sumpdfs[j] / e1_sumpdf)
            e1_sumcdf = 0.0
            for i2 in range(len(self.tab_cdf) - (self.ne2 - i), -1, -1) :
                e1_sumcdf += self.tab_cdf[i2][0]
            norm_sumcdf = e1_sumcdf / tot_sumcdf
            self.tab_ncdf.append((norm_sumcdf, norm_sumpdfs))
        return
    
    def print_tab_ncdf(self, out_ = sys.stderr) :
        out_.write("Tabulated normalized c.d.f :\n")
        for i in range(len(self.tab_ncdf)) :
            e1i = self.e1min + i * self.estep
            out_.write("{:d} E1={:.5e} MeV : ".format(i, e1i))
            out_.write("Cumul tot prob={:.16e} : ".format(self.tab_ncdf[i][0]))
            out_.write("=>  {:d} cumul prob. samples from {:.16e} to {:.16e} "
                       .format(len(self.tab_ncdf[i][1]),self.tab_ncdf[i][1][0],self.tab_ncdf[i][1][-1]))
            out_.write("\n")
        return
        
    def save_tab_ncdf(self, format_ = 1, deco_ = False):
        prob_eps=1e-7
        cdf_filename = self.ncdf_filename
        ftabcdf = open(cdf_filename, "w")
        ftabcdf.write("#isotope={}\n".format(self.isotope))
        ftabcdf.write("#dbd_ga.mode={}\n".format(self.dbd_ga_mode))
        ftabcdf.write("{:.4f}\n".format(self.qbb))
        ftabcdf.write("CumulativeProbability {:.16e} {:.16e} {:.16e} {:d}\n"
                      .format(self.e1min, self.e1max, self.estep, self.ne1))
        e1_tab_cdf = []
        if format_ == 1 :
            if deco_ :
                ftabcdf.write("#e1.cdf\n")
            for i in range(len(self.tab_ncdf)) :
                p = self.tab_ncdf[i][0]
                e1_tab_cdf.append(p)
        save_tab_cdf(e1_tab_cdf, 7, ftabcdf)
          
        for i in range(len(self.tab_ncdf)) :
            e1i = self.e1min + i * self.estep
            if deco_ :
                ftabcdf.write("\n\n#e1={:.16e}\n".format(e1i))
            if format_ != 1 :
                ftabcdf.write("{:.16e} ".format(self.tab_ncdf[i][0]))
            save_tab_cdf(self.tab_ncdf[i][1], 7, ftabcdf)
        ftabcdf.close()  
        return


def test() :

    cprobs = [ 0.232412564 , 0.32214, 0.678, 0.7879, 0.8932,
               0.92132, 0.94343, 0.976783,
               0.992132, 0.994343, 0.9976783,
               0.9992132, 0.9994424343, 0.99976783,
               0.99992187982732, 0.99994343433, 0.999976783,
               0.999992132, 0.999994343, 0.9999976783,
               0.9999992132, 0.9999994343, 0.999999767316783,
               #0.99999992132,
               0.99999994343,
               # 0.999999976783,
               #0.999999992132, 0.999999994343, 0.9999999976783,
               0.9999999992132, 0.99999999976783,
               0.99999999992132, 0.99999999994343, 0.999999999976783,
               0.999999999992132, 0.999999999994343, 0.9999999999976783, 0.9999999999986783,
               0.9999999999992132,
               1.0]
    save_tab_cdf(cprobs, 6, sys.stdout)
    return
        
if __name__ == "__main__" :
    print("Welcome in mkocdfdata", file=sys.stderr)
    if len(sys.argv) < 4 :
        raise Exception("Missing arguments : mkocdfdata.py outfile isotope g4mode Qbb ")
    pdf_filename = sys.argv[1]
    isotope = sys.argv[2]
    mode = sys.argv[3]
    qbb = float(sys.argv[4])
    print("P.D.F. filename : ", pdf_filename, file=sys.stderr)
    print("isotope : ", isotope, file=sys.stderr)
    print("mode : ", mode, file=sys.stderr)
    print("qbb : ", qbb, file=sys.stderr)
    debug = True
    app = mkocdfdata(pdf_filename, isotope, mode, qbb, debug)
    app.load_tab_pdf()
    app.print_tab_pdf()
    app.fill_tab_cdf()
    app.print_tab_cdf()
    app.fill_tab_ncdf()
    app.print_tab_ncdf()
    app.save_tab_pdf(False)
    app.save_tab_ncdf(1, False)
    sys.exit(0)
