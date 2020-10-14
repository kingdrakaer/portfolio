% Skeleton of a Hodgkin-Huxley model for the
% electrophysiology of the squid giant axon.
%
% External functions:
% get_n_rates(Vm) get_m_rates(Vm) get_h_rates(Vm)
%
%Dylan Kennedy, BME 307
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Set parameters (constants)
tStart = -1.000 ; % start time, millisec
tEnd = 15.000 ; % end time, millisec
deltaT = 0.020 ; % time step, millisec
nStep = ceil((tEnd-tStart)/deltaT) ; % number of time steps
outputInterval = 20 ; % number of time steps between screen output
Vrest = -60 ; % resting potential, mV
Cm = 1.00 %microfarads
Jstim = 150
StimDur = 150
EK = -72.1 ; %potassium nernst potential, mV
ENa = 52.4 ; % sodium Nernst potential, mV
EL = -49.187 ; %leak nernst potential, mW
gK = 0.367 %conductance per open channel of potassium
gNa = 0.011 %conductance per open channel of sodium
gK_max = 36.0 ;%potassium saturation conductance, mS/cm^2
gNa_max = 120 ; % sodium saturation conductance, mS/cm^2
gL_max= 0.3 ; %leak saturation conductance, mS/cm^
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Set initial value of state variables
Vm = Vrest ; % membrane potential, mV
n = 0.31768 ; %initial value of n gate
m = 0.05293 ; % initial value of m gate
h = 0.59612 ; %initial value of h gate
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Preallocate storage for variables to plot
plot_Vm = zeros(nStep,1) ;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Print a heading for the screen output
display('Hodgkin-Huxley squid giant axon model')
display(' i time Jion Vm dVdt n m h')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Start the simulation
tNow = tStart ;
for iStep = 1:nStep
    % Compute ion currents at tNow, then apply stimulus current
    JK = gK_max*n*n*n*n*(Vm-EK) ;
    JNa = gNa_max*m*m*m*h*(Vm-ENa) ;
    JL = gL_max*(Vm-EL) ;
    if( 0<=tNow && tNow<StimDur ) % start stimulus current at tNow=0
    Jm = Jstim ;
    else % stop stimulus when tNow = StimDur
    Jm = 0 ;
    end
    % Compute gates' opening and closing rates
    [alpha_n beta_n] = get_n_rates(Vm) ; % get potassium activation rates
    [alpha_m beta_m] = get_m_rates(Vm) ; % get sodium activation rates
    [alpha_h beta_h] = get_h_rates(Vm) ; % get sodium inactivation rates
    % Compute change in state variables
    deltaVm = ((Jm - JNa - JK - JL)/Cm) * deltaT ;
    deltan = (alpha_n*(1-n)-beta_n*n) * deltaT ;
    deltam = (alpha_m*(1-m)-beta_m*m) * deltaT ;
    deltah = (alpha_h*(1-h)-beta_h*h) * deltaT ;
    % Record/display state variables & other values
    plot_Vm(iStep) = Vm ;
    plot_n(iStep) = n ;
    plot_m(iStep) = m ;
    plot_h(iStep) = h ;
    plot_time(iStep) = tNow ;
    if mod(iStep,outputInterval) == 0
    fprintf('%5d %8.2f %8.3f %7.3f %7.2f %7.5f %7.5f %7.5f\n', ...
    iStep, tNow, Jion, Vm, dV_dt, n, m, h) ;
    end % if mod(tNow)
    % Update state variables
    Vm = Vm + deltaVm ; % new Vm = current Vm + change in Vm
    n = n + deltan ; %new n gate
    m = m + deltam ; %new m gate
    h = h + deltah ; %new h gate
    tNow = tStart + iStep*deltaT ; % increment the time
end % for iStep
% Plot the gates, probabilities, currents, Vm, etc
plot(plot_time, plot_Vm, plot_n, plot_m, plot_h); grid on ;
% end of file
